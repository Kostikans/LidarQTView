#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <liblas\liblas.hpp>
#include <liblas\header.hpp>
#include <liblas\writer.hpp>
#include <QtCore\qvector.h>
#include <QtCore\qdir.h>
#include <QtWidgets\qapplication.h>
#include <QtCore\qstring.h>

struct Point
{
public:
	float x, y, z;
	Point() {}
	Point(float _x, float _y, float _z)
	{
		x = std::move(_x);
		y = std::move(_y);
		z = std::move(_z);
	}
};

class LasParser
{
public:
	LasParser() = default;
	int Size = 0;
	QVector<Point> ReadAndCreate(const char* filePath)
	{
		std::ifstream fin;
		QString path = QFileInfo(".").absolutePath() + "/" + QApplication::applicationName() + "/" + "Layers1";

		try
		{
			fin.open(filePath, std::ios::in | std::ios::binary);
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		liblas::ReaderFactory f;
		liblas::Reader reader = f.CreateWithStream(fin);
		liblas::Header const& header = reader.GetHeader();

		qDebug() << "Compressed: " << (header.Compressed() == true);
		qDebug() << "Signature: " << QString::fromStdString(header.GetFileSignature());
		qDebug() << "Points count: " << header.GetPointRecordsCount() << '\n';

		QVector<Point> points;
		points.reserve(header.GetPointRecordsCount());
		int size = 0;

		std::ofstream ofs[68];
		int number = 0;
		for (float i = -3; i < 31; i += 1 / 2.0f)
		{
			std::ios::openmode m = std::ios::out | std::ios::in | std::ios::binary | std::ios::ate;
			//qDebug()<<QString::number(int(i)) << " " << QString::number(int((abs(int(i) - i)) * 10));
			QString name = path + "/" + QString::number(int(i)) + "_" + QString::number(int((abs(int(i) - i)) * 10)) + "layer" + ".las";
			std::string strName = name.toStdString();

			liblas::Create(ofs[number], strName);
			liblas::Open(strName, m);
			number++;
		}
		liblas::Writer* writer[68];
		for (int i = 0; i < 68; ++i)
		{
			writer[i] = new liblas::Writer(ofs[i], header);
		}
		int sizeW[68];
		for (int i = 0; i < 68; ++i)
			sizeW[i] = 0;
		while (reader.ReadNextPoint())
		{
			liblas::Point  const& p = reader.GetPoint();
			number = 0;
			for (float i = -3; i < 31; i += 1 / 2.0f)
			{
				if (p.GetZ() >= i && p.GetZ() <= (i + 0.5f))
				{
					writer[number]->WritePoint(p);
					sizeW[number]++;
				}
				number++;
			}
			if (size % 500000 == 0)
				qDebug() << "Pas" << size;
			size++;
		}

		for (int i = 0; i < 68; ++i)
		{
			liblas::Header headrwr(reader.GetHeader());
			headrwr.SetPointRecordsCount(sizeW[i]);
			writer[i]->SetHeader(headrwr);
			writer[i]->WriteHeader();
		}


		Size = size;
		return std::move(points);
	}

	QVector<Point> Read(const char* filePath)
	{
		std::ifstream fin;

		try
		{
			fin.open(filePath, std::ios::in | std::ios::binary);
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		liblas::ReaderFactory f;
		liblas::Reader reader = f.CreateWithStream(fin);
		liblas::Header const& header = reader.GetHeader();

		qDebug() << "Compressed: " << (header.Compressed() == true);
		qDebug() << "Signature: " << QString::fromStdString(header.GetFileSignature());
		qDebug() << "Points count: " << header.GetPointRecordsCount() << '\n';

		QVector<Point> points;

		points.reserve(header.GetPointRecordsCount());
		int size = 0;
		qDebug() << header.GetPointRecordsCount();
		while (reader.ReadNextPoint())
		{
			liblas::Point  const& p = reader.GetPoint();
			size++;
			points.append(Point(p.GetX(), p.GetY(), p.GetZ()));
		}
		Size = size;
		return std::move(points);
	}

	int size() const noexcept
	{
		return Size;
	}

};