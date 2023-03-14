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

chip* GetInput(){
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
    return res;
}

int main(){
    chip* ChipSet;
    ChipSet = GetInput();
    chip theGoodOne;
    theGoodOne = findGoodChip_Algorithm(ChipSet);

    delete[] ChipSet;
    return 0;
}