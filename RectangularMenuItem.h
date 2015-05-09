#ifndef RECTANGULAR_MENU_ITEM_H
#define RECTANGULAR_MENU_ITEM_H

template <typename ENUM_TYPE>
class RectangularMenuItem
{
  public:
    sf::Rect<int> mRect;
    ENUM_TYPE mAction;
        
    RectangularMenuItem (sf::Rect<int>& r, ENUM_TYPE a) : mRect {r}, mAction {a}
      { }
    RectangularMenuItem (sf::Rect<int>&& r, ENUM_TYPE a) : mRect {std::move(r)}, mAction {a}
      { }

    bool operator== (const RectangularMenuItem& rhs) {
      return (this->mAction == rhs.mAction);
    }
    RectangularMenuItem& operator= (const RectangularMenuItem& rhs) {
      RectangularMenuItem<ENUM_TYPE> copy = rhs;
      std::swap(*this,copy);
      return *this;
    }
    RectangularMenuItem& operator= (RectangularMenuItem& rhs) {
      std::swap(mAction,rhs.mAction);
      std::swap(mRect,rhs.mRect);
      return *this;
    }
};

#endif
