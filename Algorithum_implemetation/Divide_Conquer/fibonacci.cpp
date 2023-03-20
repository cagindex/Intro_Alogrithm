/**
 * calculate the fibonacci using matrix multiplication
 * M[n] = MI*M[n-1]
 * M[n] = MI**2 * M[n-2]
 * M[n] = MI**n * M[0]
 * Turn question into calculate the matrix in n times
*/

#include<iostream>
using namespace std;

typedef unsigned long long Matrix_Element;

class matrix{
	public:
		//constructor
		explicit matrix(int row, int column):rowNum(row),columnNum(column),contain(new Matrix_Element[row*column]){}

		//copy constructor
		matrix(const matrix& m){
			rowNum = m.rowNum;
			columnNum = m.columnNum;
			contain = new Matrix_Element[rowNum*columnNum];

			memcpy(contain, m.contain, sizeof(Matrix_Element)*rowNum*columnNum);
			/**
			 * 上面的memcpy有问题，因为这是复制构造函数不会调用构造函数（两者平级），也就是说再构造函数里面
			 * 有对contain的分配，所以地址就是在堆里面（0x7f8b28705ac0)
			 * 但是在这个复制构造函数里面你没有分配位置，所以编译器会随机给位置（比如0x10f477060 0x10e093060等等（全看编译器心情））
			 * 但是这个不保证访问了一个不允许的区域，所以导致了bus error
			 * 为了解决这个问题：
			 * 1、分配堆空间
			 * 2、将operator那里堆返回值改为非常量右值，这里调用另一个移动构造函数
			 * 3、使用move函数将返回值改为非常量右值，调用移动构造函数
			*/
		}
		//move constructor
		matrix(matrix&& m){
			rowNum = m.rowNum;
			columnNum = m.columnNum;
			contain = m.contain;

			m.contain = nullptr;
		}


		//destructor
		~matrix(){
			if (contain != nullptr){
				delete[] contain;
			}
		}
		
		/**
		 * basic function
		*/

		/**
		 * 返回行数
		*/
		int GetRowNum(){
			return rowNum;
		}
		/**
		 * 返回列数
		*/
		int GetColumnNum(){
			return columnNum;
		} 
		/**
		 * 将传入的this指针const化（一般是不const的）
		 * 这样可以保证const matrix& 调用这个函数的时候不会报错
		 * 
		 * 因为const matrix& 相当于不能修改其中的值 也就是 const matrix* const
		 * 一般的matrix& 不能修改指针但是可以修改内容，也就是 matrix* const
		 * 
		 * 一般的内置函数会隐式传递this指针，一般而言this指针是不能修改this值，但是可以修改内容，也就是 matrix* const
		 * 但是对于const matrix&会隐式传递 const matrix* const 不能被转换为matrix* const所以报错
		*/

		/**
		 * rowIndex->行号（0为第一个）
		 * columnIndex->列号（0为第一个）
		 * 根据上述两个参数返回对应的值
		*/
		Matrix_Element GetPosition (int rowIndex, int columnIndex) const {
			int index;
			index = rowIndex*columnNum + columnIndex; 
			return contain[index];
		}
		void PutPosition(int rowIndex, int columnIndex, Matrix_Element content){
			int index;
			index = rowIndex*columnNum + columnIndex; 
			contain[index] = content;
		}
		bool CheckRight(const matrix& otherMatrix) const {
			//check if this matrix can multy with othermatrix in the right
			if (columnNum == otherMatrix.rowNum){return true;}
			return false;
		}

		/**
		 * Advanced function
		*/
		matrix operator*(const matrix& otherMatrix) const {
			if (! (*this).CheckRight(otherMatrix)){return *(new matrix(0, 0));}
			matrix* resPointer = new matrix(rowNum, otherMatrix.columnNum);
			int i, j, rowIndex, columnIndex, midLen;
			Matrix_Element content = 0;
			midLen = columnNum;
			
			for(i = 0; i < (resPointer->rowNum)*(resPointer->columnNum); i++){
				rowIndex = i / (resPointer->columnNum);
				columnIndex = i % (resPointer->columnNum);

				for (j = 0; j < midLen; j++){
					content += ((*this).GetPosition(rowIndex, j)) * (otherMatrix.GetPosition(j, columnIndex));
				}
				resPointer->PutPosition(rowIndex, columnIndex, content);
				content = 0;
			}
			return *resPointer;
		}
	private:
		int rowNum;
		int columnNum;
		Matrix_Element* contain;
};

/**
 * multimatrix
*/
matrix multiMatrix(const matrix& m, int n){
	if(n == 2){ return m*m;}
	if(n == 1){ return m;}

	matrix s = multiMatrix(m, n/2);
	if (n%2){
		return multiMatrix(s, 2)*m;
	}
	return multiMatrix(s, 2);
}

/**
 * fibonacci_Algorithm implementation
*/
Matrix_Element fibonacci_Algorithm(int n){
	if (n == 0) {return 0;}
	matrix I_(2, 2);
	matrix init_(2, 1);

	I_.PutPosition(0, 0, 1);
	I_.PutPosition(0, 1, 1);
	I_.PutPosition(1, 0, 1);
	I_.PutPosition(1, 1, 0);
	init_.PutPosition(0, 0, 1);
	init_.PutPosition(1, 0, 0);

	matrix result = multiMatrix(I_, n)*init_;
	return result.GetPosition(1, 0);
}

void print(int n, Matrix_Element res){
	printf("The %dth fibonacci num is : %llu\n", n, res);
}

int main(){
	int n;
	Matrix_Element result;
	cin >> n;

	result = fibonacci_Algorithm(n);
	print(n, result);
	return 0;
}