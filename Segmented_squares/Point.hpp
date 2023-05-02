
/**
 * @class Point
 * 
 * @brief A class representing a point in a 2D space The Point class contains two integer variables: first and second, representing the x and y coordinates of a point in a 2D space. The class provides three comparison operators: <, >, and ==, which compare two points based on their x and y coordinates.
 * 
 */
class Point
{
public:
    int first;
    int second;
    Point(int x, int y)
    {
        first = x;
        second = y;
    }
    Point()
    {
    }
   bool operator < (const Point& p) const {
		return first < p.first;
	}
    bool operator > (const Point& p ) const{
        return second>p.second;
    }
    bool operator ==(const Point& p) const{
        return first==p.first and second==p.second;
    }
};