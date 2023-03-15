#include<iostream>
using namespace std;

class chip{
    private:
        bool quality;
    public:
        chip(){quality = false;};
        explicit chip(bool q){quality = q;}

        int Check(chip* other){
            /**
             * return int for good or not
             * there are four situations : 00 01 10 11
             * the first bit stands for the quality of the this chip
             * the second bit stands for the qulity of the tested chip
             * but it may useless or may not allowed to distinguish this.
            */
            bool myReport, otherReport;
            if (this->quality == true){
                myReport = (*other).GetQuality();
            }
            else{
                if (rand()%2){myReport = true;}
                else {myReport = false;}
            }

            if ((*other).GetQuality() == true){
                otherReport = this->quality;
            }
            else{
                if (rand()%2){ otherReport = true;}
                else {otherReport = false;}
            }
            return (myReport << 1) | (otherReport);
        }

        bool GetQuality(){
            return quality;
        }

        void WriteQuality(bool qua){
            quality = qua;
        }
};

struct chipList{
    chip* chipPointer;
    int listLen;

    explicit chipList(chip* a, int len):chipPointer(a),listLen(len){}
    //copy constructor
    chipList(const chipList& chipset){
        chipPointer = new chip[listLen];
        listLen = chipset.listLen;
        cout << chipPointer << endl;
        memcpy(chipPointer, chipset.chipPointer, sizeof(chip)*listLen);
    }
    //move constructor
    chipList(chipList&& chipset){
        chipPointer = chipset.chipPointer;
        listLen = chipset.listLen;
        chipset.chipPointer = nullptr;
    }
    //Destructor
    ~chipList(){
        // if(chipPointer != nullptr){
        //     delete[] chipPointer;
        // }
    }
};

chipList GetInput(){
    int lineNum, maxLine, tmp;
    /**
     * 0 for false
     * 1 for true
    */
    cin >> lineNum;
    maxLine = lineNum;
    chip* res = new chip[lineNum];
    while (lineNum) {
        cin >> tmp;
        res[maxLine - lineNum].WriteQuality(tmp);
        lineNum --;
    }
    struct chipList tmpStruct(res, maxLine);

    return tmpStruct;
}

chip findGoodChip_Algorithm(chip* ChipSet, int chipLen){
    /// @brief find the good chip in set which num of good ones is bigger than bad ones.
    /// @param ChipSet 
    /// @return a good chip
    /**
     * 采用分治策略，将数组两两一组，（假设余一个）两两做如下策略：
     * 如果两个都报好，则随便取一个
     * 反之则全不要
     * 将策略实施之后，得到的组，如果是奇数个，则余下的那一个不要，如果是偶数，则加入余下的那一个
     * 之后继续，直到剩下一个，返回。
     * （启发：找到循环不变量）
    */
    if (chipLen == 1){return *ChipSet;}
    int loopCnt, remainOne, nextIndex, i;
    loopCnt = chipLen/2;
    remainOne = loopCnt - (loopCnt*2);
    nextIndex = 0;

    chip* nextSet = new chip[loopCnt + remainOne];
    //实施策略
    for (i = 0; i < loopCnt; i++){
        if (ChipSet[2*i].Check(&ChipSet[2*i+1]) == 3){
            //如果两个都报好，则随便取一个加入nextSet
            nextSet[nextIndex].WriteQuality(ChipSet[2*i].GetQuality());
            nextIndex++;
        }
    }
    //最后如果nextSet中数量为奇数则不要剩余的，若为偶数则加入余下的那个
    if (remainOne && (nextIndex % 2 == 0)){
        nextSet[nextIndex].WriteQuality(ChipSet[chipLen - 1].GetQuality());
        nextIndex ++;
    }

    //释放栈内存
    delete[] ChipSet;
    return findGoodChip_Algorithm(nextSet, nextIndex);
}

void main_check(chip theOne){
    if (theOne.GetQuality()){
        cout << "This one is good, congratulations!" << endl;
        return ;
    }
    cout << "This one is bad, please fix the code TAT" << endl;
    return ;
}

int main(){
    struct chipList ChipSet = GetInput();
    chip theGoodOne;
    theGoodOne = findGoodChip_Algorithm(ChipSet.chipPointer, ChipSet.listLen);

    main_check(theGoodOne);
    return 0;
}