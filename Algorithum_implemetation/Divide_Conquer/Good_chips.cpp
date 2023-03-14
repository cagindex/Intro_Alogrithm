#include<iostream>
using namespace std;

class chip{
    private:
        bool quality;
    public:
        chip(){};
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

    explicit chipList(chip* a, int len):chipPointer(a),listLen(len){cout << "constructor called" << endl;}
    chipList(const chipList& chipset){
        chipPointer = new chip[listLen];
        listLen = chipset.listLen;
        cout << chipPointer << endl;
        memcpy(chipPointer, chipset.chipPointer, sizeof(chip)*listLen);
    }
};

struct chipList GetInput(){
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

    cout << tmpStruct.chipPointer << endl;
    return tmpStruct;
}

chip findGoodChip_Algorithm(chip* ChipSet){
    /// @brief find the good chip in set which num of good ones is bigger than bad ones.
    /// @param ChipSet 
    /// @return a good chip
    return chip(0);
}

int main(){
    struct chipList ChipSet = GetInput();
    chip theGoodOne;
    cout << ChipSet.chipPointer << endl;
    return 0;
}