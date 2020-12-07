/*참조 하세요*/

//사진 랜덤 오픈은 나중에, 열리는 사진 고정이라고 가정
int main(void)
{   
    char pic_num=0;                   //현재 사진이 몇번 사진인지 알려주는 변수
    
    show("start_pic);
    
    if(press home button){
    show("puzzle3.bmp");              //초기 화면에 puzzle3을 띄워줌
    pic_num=3;                        //동시에 pic_num의 3을 on 시켜줌
    }

    while(1){

    switch(pic_num)
    {
    /*puzzle1번 사진이 떠있는경우-> 게임종료*/
     case 1:                          //puzzle1번 사진이 떠있는경우
            show ("end_pic.bmp");      //게임 종료안내 
										//while 문 빠져나가기(작성해야댐)
     break;

/*puzzle2번 사진이 떠있는경우*/
     case 2:                          
        if(1번버튼 && 2번버튼)
            show(p_5);
                pic_num=5;
        else if (1번 && 3번)
             show(p_4);
             pic_num=4;
        else if (2번 && 3번)
               show(p_1);
               pic_num=1;
     break;
     
/*puzzle 3번 이 떠있을때*/
     case 3:
         if(1번버튼 && 2번버튼)
            show(p_1);
                pic_num=1;
        else if (1번 && 3번)
             show(p_5);
             pic_num=5;
        else if (2번 && 3번)
               show(p_4);
               pic_num=4;
     break;

/*puzzle 4번 이 떠있을때*/
     case 4:
         if(1번버튼 && 2번버튼)
            show(p_6);
                pic_num=6;
        else if (1번 && 3번)
             show(p_2);
             pic_num=2;
        else if (2번 && 3번)
               show(p_3);
               pic_num=3;       
     break;

/*puzzle 5번 이 떠있을때*/
     case 5:
         if(1번버튼 && 2번버튼)
            show(p_2);
                pic_num=2;
        else if (1번 && 3번)
             show(p_3);
             pic_num=3;
        else if (2번 && 3번)
               show(p_6);
               pic_num=6;
     break;

/*puzzle 6번 이 떠있을때*/
     case 6:
         if(1번버튼 && 2번버튼)
            show(p_4);
                pic_num=4;
        else if (1번 && 3번)
             show(p_1);
             pic_num=1;
        else if (2번 && 3번)
               show(p_5);
               pic_num=5;
     break;
    }

}
