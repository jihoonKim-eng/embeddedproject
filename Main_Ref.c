/*참조 하세요*/

//사진 랜덤 오픈은 나중에, 열리는 사진 고정이라고 가정
int main(void)
{   
    char pic_num=0;                   //현재 사진이 몇번 사진인지 알려주는 변수
    
    show("puzzle3.bmp");              //초기 화면에 puzzle3을 띄워줌
    pic_num=3;                        //동시에 pic_num의 3을 on 시켜줌

while(1){

    switch(pic_num)
    {
     case 1:                          //puzzle1번 사진이 떠있는경우
            show ("게임종료.bmp");      //게임 종료안내, while 문 빠져나가기
     break;


     case 2:                          //puzzle2번 사진이 떠있는경우
        if(1번버튼 && 2번버튼)
            show(p_5);
                pic_num=5;
        else if (1번 && 3번)
             show(p_4);
        else if (2번 && 3번)
               show(p_1);

     break;

     case 3:
        
     break;


     case 4:
        
     break;


     case 5:
        
     break;


     case 6:
        
     break;
    }

}
