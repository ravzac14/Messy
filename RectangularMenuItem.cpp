/* Logic for a button,
 *  a 'RectangularMenuItem'
 */

RectangularMenuItem::RectangularMenuItem<ENUM_TYPE> (sf::Rect<int>& r, ENUM_TYPE a) : mRect {r}, mAction {a} 
{ }

RectangularMenuItem::RectangularMenuItem<ENUM_TYPE> (sf::Rect<int>&& r, ENUM_TYPE a) : mRect {std::move(r)}, mAction {a} 
{ }

bool RectangularMenuItem::operator== (const RectangularMenuItem& rhs) 
{
  return (this->mAction == rhs.mAction);
}

RectangularMenuItem<ENUM_TYPE>& RectangularMenuItem::operator= (const RectangularMenuItem& rhs) 
{
  RectangularMenuItem<ENUM_TYPE> copy = rhs;
  std::swap(*this,copy);
  return *this;
}

RectangularMenuItem<ENUMTYPE>& RectangularMenuItem::operator= (RectangularMenuItem& rhs) 
{
  std::swap(mAction,rhs.mAction);
  std::swap(mRect,rhs.mRect);
  return *this;
}

