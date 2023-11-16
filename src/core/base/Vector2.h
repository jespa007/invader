#pragma once


/**
 * A 2-element vector that is represented by single-precision floating point
 * x,y coordinates.  If this value represents a normal, then it should
 * be normalized.
 *
 */
template <typename _T>
class Vector2 {

public:

	_T x,y;

    /**
     * Return total data bytes have Vector2
     * return return number size of bytes of Vector2
     */
	static int sizeNumBytes(){return sizeof(_T)*2;}

    /**
     * Constructs and initializes a Vector2 from the specified xyz coordinates.
     * param x the x coordinate
     * param y the y coordinate
     */
    Vector2(_T x, _T y)
    {
		this->x = x;
		this->y = y;
    }


    /**
     * Constructs and initializes a Vector2 from the array of length 2.
     * param v the array of length 2 containing xy in order
     */
    Vector2(const std::vector<_T> & v)
    {

    	assert(v.size() == 2);

       this->x = v[0];
       this->y = v[1];
    }


    /**
     * Constructs and initializes a Vector2 from the specified Vector2.
     * param v1 the Vector2 containing the initialization x y data
     */
    Vector2(const Vector2<_T> & v1)
    {
       this->x = v1.x;
       this->y = v1.y;

    }

    /**
     * Constructs and initializes a Vector2 to (0,0).
     */
    Vector2()
    {
			x = y = 0;
    }


   /**
     * Returns the squared length of this vector.
     * return the squared length of this vector
     */
    float lengthSquared()
    {
        return (this->x*this->x + this->y*this->y);
    }

    void set(_T x, _T y)
    {
    	this->x = x;
    	this->y = y;
    }

    void set(const Vector2<_T>& v)
    {
    	this->x = v.x;
    	this->y = v.y;
    }

    void set(Vector2<_T>& v)
    {
    	this->x = v.x;
    	this->y = v.y;
    }

    /**
     * Returns the length of this vector.
     * return the length of this vector
     */
    float length()
    {
        return (float)
             sqrt(this->x*this->x + this->y*this->y);
    }

 /**
   * Computes the dot product of this vector and vector v1.
   * param v1 the other vector
   * return the dot product of this vector and v1
   */
  float dot(const Vector2 & v1)
    {

      return (this->x*v1.x)+(this->y*v1.y);
    }



   /**
     * Sets the value of this vector to the normalization of vector v1.
     * param v1 the un-normalized vector
     */
    void normalize(const Vector2 & v1)
    {
        float norm;

        norm = (float) (1.0/sqrt(v1.x*v1.x + v1.y*v1.y));
        this->x = v1.x*norm;
        this->y = v1.y*norm;

    }

    /**
     * Normalizes this vector in place.
     */
    void normalize()
    {
        float norm;

        float sum = (this->x*this->x + this->y*this->y );

        if(sum == 0)
        	norm = 0;
		else
        norm = (float)
               (1.0/sqrt(this->x*this->x + this->y*this->y ));

        this->x *= norm;
        this->y *= norm;
    }

    /**
      * Negate vector.
      */
     void negate()
       {
         this->x=-this->x;
         this->y=-this->y;
       }


  /**
    *   Returns the angle in radians between this vector and the vector
    *   parameter; the return value is constrained to the range [0,PI].
    *   param v1    the other vector
    *   return   the angle in radians in the range [0,PI]
    */
   float angle(const Vector2 & v1)
   {
      double vDot = this->dot(v1) / ( this->length()*v1.size() );
      if( vDot < -1.0) vDot = -1.0;
      if( vDot >  1.0) vDot =  1.0;
      return((float) (acos( vDot )));
   }


   void scale(float _s)
   {
   		this->x*=_s;
   		this->y*=_s;
   }

   void add(const Vector2 & v1) {

   		this->x += v1.x;
   		this->y += v1.y;
   }

   void sub(const Vector2 & v1) {

   		this->x -= v1.x;
   		this->y -= v1.y;
   }

   void mul(const Vector2 & v1) {

   		this->x *= v1.x;
   		this->y *= v1.y;
   }


   bool operator == (const Vector2<_T> & v) {

   		return (this->x == v.x && this->y);
   }

   bool operator != (const Vector2<_T> & v) {

   		return (!(*this == v));
   }

   Vector2<_T> & operator = (const Vector2<_T> & _op2){
   	this->x = _op2.x;
   	this->y = _op2.y;
   	return (*this);
   }

   Vector2<_T> & operator += (const Vector2<_T> & _op2){
   	this->x += _op2.x;
   	this->y += _op2.y;
   	return (*this);
   }

   friend Vector2<_T> operator +(const Vector2<_T> & _op1, const Vector2<_T> & _op2){
	   Vector2<_T> res;
	   res.x = _op1.x + _op2.x;
	   res.y = _op1.y + _op2.y;
	   return res;
   }


   friend  Vector2<_T> operator -(const Vector2<_T> & _op1, const Vector2<_T> & _op2){
	   Vector2<_T> res;
	   res.x = _op1.x - _op2.x;
	   res.y = _op1.y - _op2.y;
	   return res;
   }

   friend  Vector2<_T> operator *(const Vector2<_T> & _op1,float _s)
   {
	   Vector2<_T> res;
	   res.x = _op1.x*_s;
 	   res.y = _op1.y*_s;
 	   return res;
   }

   Vector2<_T> & operator *=(float _s)
   {
	   	this->x *= _s;
	   	this->y *= _s;
	   	return (*this);
   }
};


typedef Vector2<float> 	Vector2f,Point2f;
typedef Vector2<int> 		Vector2i,Point2i;

