#ifndef PATH_TO_MESSAGE_H
#define PATH_TO_MESSAGE_H

#include "GameMessage.h"
#include "Vector2D.h"

class SmoothPathFinding;

class PathToMessage : public GameMessage
{
public:
	PathToMessage(const Vector2D& from, const Vector2D& to);
	~PathToMessage();

	const Vector2D& getFrom() const { return mFrom; };
	const Vector2D& getTo() const { return mTo; };

	void process();

private:
	Vector2D mFrom;
	Vector2D mTo;
	SmoothPathFinding* smoothPath;
};

#endif // !PATH_TO_MESSAGE_H
