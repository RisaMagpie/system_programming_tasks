#include <MyArray2D.cc>

template<typename Z>
class MyMaskedArray2D{
  MyArray2D<Z>* array2DPtr;
  MyArray2D<bool>* maskPtr;
public:
  //operator=
  MyMaskedArray2D& operator=(const Z num) {
		for (int rowCounter=0;rowCounter<array2DPtr->rows;rowCounter++){
      for(int colCounter=0;colCounter<array2DPtr->cols;colCounter++){
        if(maskPtr[rowCounter][colCounter]){
          this->array2DPtr[rowCounter][colCounter] = num;
        };
      };
    };
	}
};
int main(){
  return 0;
}