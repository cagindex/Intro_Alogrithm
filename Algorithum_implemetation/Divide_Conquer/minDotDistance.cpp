#include<iostream>
#include<cmath>
using namespace std;

class dot{
	public:
		//Constructor
		dot(){}
		dot(double x, double y, int id_):id(id_),xx(x),yy(y){}
		//Copy constructor
		dot(const dot& otherDot){
			id = otherDot.id;
			xx = otherDot.xx;
			yy = otherDot.yy;
		}
		//Destructor
		~dot(){}

		/**
		 * Basic Function
		*/

		/**
		 * Get id
		*/
		int GetId() const { return id; }
		/**
		 * Get xx 
		*/
		double GetXx() const { return xx; }
		/**
		 * Get yy
		*/
		double GetYy() const { return yy; }
		/**
		 * Set xx and yy
		*/
		void SetXxYy(double xx_, double yy_) { xx = xx_; yy = yy_; }

		/**
		 * Advanced function
		*/
		double CalcuDistance(dot& other){
			double dx = (other.xx - xx);
			double dy = (other.yy - yy);
			return sqrt(dx*dx + dy*dy);
		}

	private:
		int id;
		double xx;
		double yy;
};

typedef struct dotSet{
	int setLen;
	dot** dotPointer;

	dotSet(int len):dotPointer(new dot*[len]),setLen(len){}
	//copy constructor
	dotSet(dotSet& dotOther){
		setLen = dotOther.setLen;
		dotPointer = new dot*[setLen];
		for(int i = 0; i < setLen; i++){
			dotPointer[i] = new dot();
			memcpy(dotPointer[i], dotOther.dotPointer[i], sizeof(dot));
		}
	}
	//move constructor
	dotSet(dotSet&& dotOther){
		setLen = dotOther.setLen;
		dotPointer = dotOther.dotPointer;
		dotOther.dotPointer = nullptr;
	}
	//destructor
	~dotSet(){
		if(dotPointer != nullptr){
			for(int i = 0; i < setLen; i++){
				free(dotPointer[i]);
			}
			delete[] dotPointer;
		}
	}

	void PutDot(dot& candidate, int index){
		dotPointer[index] = &candidate;
	} 

	dot& GetIndex(int index){
		return *dotPointer[index];
	}
}dotSet;

typedef struct valueDotPair{
	int value;
	dot* theDot;
	valueDotPair(int v, dot* d):value(v),theDot(d){}
	void SetValue(int v){value = v;}
	void SetDot(dot* theOne){theDot = theOne;}
	void Set(int v, dot* one){SetValue(v); SetDot(one);}
}valueDotPair;

typedef struct resPair{
	dot* a;
	dot* b;
	resPair(){}
	resPair(dot* a_, dot* b_):a(a_),b(b_){}
	resPair(resPair& r){
		a = r.a;
		b = r.b;
	}
	void operator=(resPair& r){
		a = r.a;
		b = r.b;
	}
}resPair;

dotSet GetInput(int dotNum){
	int index, x, y;
	dotSet res(dotNum);

	for(index = 0; index < dotNum; index++){
		cin >> x >> y;
		res.PutDot(*(new dot(x, y, index)), index);
	}
	return res;
}

////////////////////////
// Algorithm section starts
///////////////////////

/**
 * Quick sort
*/
void swap(valueDotPair** preX, int i, int j){
	valueDotPair* tmp = preX[i];
	preX[i] = preX[j];
	preX[j] = tmp;
}
int partion(valueDotPair** preX, int start, int end, bool (*fp)(valueDotPair*, valueDotPair*)){
	int i, j;
	valueDotPair* x;
	x = preX[start];
	i = start+1;
	j = end;
	while(1){
		while(!fp(preX[i], x) && i < end){ i++; }
		while(fp(preX[j], x) && j > start){ j--; }
		if (j <= i){return j;}
		else{ swap(preX, i, j); }
	}
}
void QuickSort(valueDotPair** preX, int start, int end, bool (*fp)(valueDotPair*, valueDotPair*)){
	int i, j, midIndex;
	if (end <= start) {return ;}
	i = start + 1;
	j = end;
	midIndex = partion(preX, start, end, fp);
	swap(preX, start, midIndex);
	QuickSort(preX, start, midIndex - 1, fp);
	QuickSort(preX, midIndex + 1, end, fp);
}

bool MaxOrNot(valueDotPair* a, valueDotPair* b){
	if(a->theDot->GetXx() > b->theDot->GetXx()){
		return true;
	}
	return false;
}
/**
 * 预处理之后的算法
*/
resPair& FindMinDistance_2(valueDotPair** preX, int startIndex, int endIndex, int len){
	if ((endIndex - startIndex) == 2){
		return *new resPair(preX[endIndex]->theDot, preX[startIndex]->theDot);
	}
	if ((endIndex - startIndex) == 3){
		resPair* minPair = new resPair();
		double mmmDis = preX[startIndex+1]->theDot->CalcuDistance(*(preX[startIndex+2]->theDot));
		double tmp = mmmDis;
		minPair->a = preX[startIndex+1]->theDot;
		minPair->b = preX[startIndex+2]->theDot;

		tmp = preX[startIndex]->theDot->CalcuDistance(*(preX[startIndex+1]->theDot));
		if (tmp < mmmDis){
			minPair->a = preX[startIndex]->theDot;
			minPair->b = preX[startIndex+1]->theDot;
		}

		tmp = preX[startIndex]->theDot->CalcuDistance(*(preX[startIndex+2]->theDot));
		if (tmp < mmmDis){
			minPair->a = preX[startIndex]->theDot;
			minPair->b = preX[startIndex+2]->theDot;
		}

		return *minPair;
	}
	double minLeft, minRight, theta;
	int midIndex;
	midIndex = (startIndex + endIndex)/2;

	resPair left = FindMinDistance_2(preX, startIndex, midIndex, len);
	minLeft = left.a->CalcuDistance(*left.b);
	resPair right = FindMinDistance_2(preX, midIndex + 1, endIndex, len);
	minRight = right.a->CalcuDistance(*right.b);
	resPair* res_theta = new resPair();

	if(minRight > minLeft){
		theta = minLeft;
		*res_theta = left;
	}
	else{
		theta = minRight;
		*res_theta = right;
	}

	/**
	 * 对中间部位进行处理
	*/
	double minDis, r;
	resPair* mid = new resPair();
	for(int i = 0; i <= midIndex; i++){
		if(i >= (midIndex - theta)){
			/**
			 * 找到最小的值，理论上说应该是O（n）的情况
			 * 但是事实好像你找到那个区间也会花费n的时间复杂度，所以基本上就是logn的复杂度
			*/
			minDis = 0x7ff0000000000000;
			for (int j = midIndex+1; j < midIndex + theta; j++){
				r = preX[i]->theDot->CalcuDistance(*(preX[j]->theDot));
				if (r < minDis){
					minDis = r;
					mid->a = preX[i]->theDot;
					mid->b = preX[j]->theDot;
				}
			}
		}
	}
	if(theta < minDis){
		free(mid);
		return *res_theta;
	}
	free(res_theta);
	return *mid;

}
/**
 * Implentation of find min distance algorithm
*/
resPair& FindMinDistance_Algorithm(dotSet& initState){
	/**
	 * 首先用数组储存各个数
	 * 然后预处理，将两个数组排序
	 * 之后再进行算法的设计 
	*/
	valueDotPair** preX = new valueDotPair*[initState.setLen];
	for(int i = 0; i < initState.setLen; i++){
		preX[i] = new valueDotPair(initState.GetIndex(i).GetXx(), &initState.GetIndex(i));
	}

	/**
	 * 预处理
	*/
	typedef bool (*check)(valueDotPair*, valueDotPair*);
	check fp = MaxOrNot;
	QuickSort(preX, 0, initState.setLen - 1, fp);
	return FindMinDistance_2(preX, 0, initState.setLen-1, initState.setLen);
}

///////////////////////
// Algorithm section ends
///////////////////////
void pprint(resPair& res){
	printf("The nearest dot pair\n");
	printf("Dot1 X:%f	Y:%f\n", res.a->GetXx(), res.a->GetYy());
	printf("Dot2 X:%f	Y:%f\n", res.b->GetXx(), res.b->GetYy());
}
int main(){
	int dotNum;
	cin >> dotNum;

	dotSet initState = GetInput(dotNum);
	resPair res = FindMinDistance_Algorithm(initState);
	pprint(res);
	return 0;
}


/**
 * Things to be done
 * 首先吧quicksort拓展成要函数指针调用，用比较函数比较 2023\3\16
*/