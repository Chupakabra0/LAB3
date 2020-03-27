#pragma once
#include <SFML/Graphics.hpp>

#include "XY.h"
#include "Scale.h"
#include "Angle.h"

struct IHistory {															// ��������� ������� �������
	virtual void PreviousCondition()				  abstract;
	virtual void RememberCondition()				  abstract;
	virtual void FirstCondition()					  abstract;
};
//-----------------------------------------------------------------------------------------------------------------------------------------------
struct IMove : virtual IHistory {											// ��������� ������������
	virtual XY   GetPosition()						  abstract;
	virtual void SetPosition(XY xy)					  abstract;
	virtual void ChangePosition(XY xy)				  abstract;
};
//-----------------------------------------------------------------------------------------------------------------------------------------------
struct IRotate : virtual IHistory {											// ��������� �������� 
	virtual Angle GetAngle()						  abstract;
	virtual void  SetAngle(Angle angle)				  abstract;
	virtual void  ChangeAngle(Angle angle)			  abstract;
};
//-----------------------------------------------------------------------------------------------------------------------------------------------
struct IDraw : virtual IHistory {											// ��������� ���������
	virtual void	   Draw(sf::RenderWindow& window) abstract;
	virtual void	   SetColor(sf::Color rgba)		  abstract;
	virtual sf::Color  GetColor()					  abstract;
	virtual sf::Shape* GetPicture()					  abstract;
};
//-----------------------------------------------------------------------------------------------------------------------------------------------
struct IScale : virtual IHistory {											// ��������� ���������������
	virtual Scale GetScale()						  abstract;
	virtual void  SetScale(Scale scale)				  abstract;
	virtual void  ChangeScale(Scale scale)			  abstract;
};