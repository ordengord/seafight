#pragma once

enum E_DIRECTION {VERTICAL, HORIZONTAL, NONE};
const int MAX_LENGTH = 4;
const int SHIP_TYPE_COUNT = 4;
const int FIELD_SIZE = 10;
const int MAX_SHIP_COUNT = 10;

typedef struct ShipDataType
{
	int topLeftRow;
	int topLeftColumn;
	int length;
	E_DIRECTION direction;

	ShipDataType(){}
	ShipDataType(int r, int c, int l, E_DIRECTION d) : topLeftRow(r), 
		topLeftColumn(c), length(l), direction(d) {}
} 
ShipData;

typedef struct CellDataType
{
	int row;
	int column;

	CellDataType(){}
	CellDataType(int r, int c) : row(r), column(c) {}
}
CellData;

