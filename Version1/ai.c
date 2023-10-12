#define CsBot_AI_H//DO NOT delete this line
#ifndef CSBOT_REAL
#include <windows.h>
#include <stdio.h>
#include <math.h>
#define DLL_EXPORT extern __declspec(dllexport)
#define false 0
#define true 1
#endif
//The robot ID : six chars unique CID.
//Find it from your CoSpace Robot label or CoSpace program download GUI.
//Don't write the below line into two lines or more lines.
char AI_MyID[6] = {'1','2','3','4','5','6'};

int Dur = 0; // Duration Time to Calculate Time for normal actions
int SupDur = 0;  // Super Duration to Calculate for Super actions
int bGameEnd = false; // Is Game Over ?
int CurAction = -1; // when to do what action
int CurGame = 0; // in which game world our robor is?
int SObj_Num = 0; // how many super object do we have to pock
int SObj_X = 0; // super object X position in World 2
int SObj_Y = 0; // super object Y position in World 2
int Teleport = 0; // In which position our robot teleports
int TeleTime = 0; // when our robot teleport
int ObjInTrunk = 0; // how many object does our robot has in trunk
int USFront = 0;//UltraSonic Front
int USLeft = 0;//UltraSonic Left
int USRight = 0;//UltraSonic Right
int CSLeft_R = 0;
int CSLeft_G = 0;
int CSLeft_B = 0;
int CSRight_R = 0;
int CSRight_G = 0;
int CSRight_B = 0;
int PosX = 0; // Position X in world 1
int PosY = 0; // position Y in world 2
int TM_State = 0;
int Compass = 0;//
int Time = 0;
int WheelLeft = 0;
int WheelRight = 0;
int LED_1 = 0;
int MyState = 0;
int AI_TeamID = 1;   //Robot Team ID. 1:Blue Ream; 2:Red Team.
int MySMS; 

//The following three variables save the information of the other robot.
int OtherRob_SMS; //Keep the recieved value of the other robot MySMS value.
            //In Super Team mode, this value is sent by your another robot.
            //In Indiviual Mode, this value has no meaning.
int OtherRob_PosX;//The X coordinate of the other robot. 
int OtherRob_PosY;//The Y coordinate of the other robot. 

//The following four variables keep the information of the last state-changed object.
int ObjState;    //The state (0: Disappear; 1:Appear.) of the last state changed object.
int ObjPosX;//The X coordinate of the last state-changed object.
int ObjPosY;//The Y coordinate of the last state-changed object.
int ObjDur; //The Dur(seconds) of the object maintains the current state;
#define CsBot_AI_C
DLL_EXPORT void SetGameID(int GameID)
{
    if(CurGame != GameID) ObjInTrunk = 0;
    CurGame = GameID;
    bGameEnd = 0;
}
DLL_EXPORT void SetTeamID(int TeamID)
{
    AI_TeamID = TeamID;
}

DLL_EXPORT int GetGameID()
{
    return CurGame;
}

//Only Used by CsBot Dance Platform
DLL_EXPORT int IsGameEnd()
{
    return bGameEnd;
}

#ifndef CSBOT_REAL

char info[3000];
DLL_EXPORT char* GetDebugInfo()
{
    sprintf(info, "Dur=%d;SupDur=%d;bGameEnd=%d;CurAction=%d;CurGame=%d;SObj_Num=%d;SObj_X=%d;SObj_Y=%d;Teleport=%d;ObjInTrunk=%d;USFront=%d;USLeft=%d;USRight=%d;CSLeft_R=%d;CSLeft_G=%d;CSLeft_B=%d;CSRight_R=%d;CSRight_G=%d;CSRight_B=%d;PosX=%d;PosY=%d;TM_State=%d;Compass=%d;Time=%d;WheelLeft=%d;WheelRight=%d;LED_1=%d;MyState=%d;",Dur,SupDur,bGameEnd,CurAction,CurGame,SObj_Num,SObj_X,SObj_Y,Teleport,ObjInTrunk,USFront,USLeft,USRight,CSLeft_R,CSLeft_G,CSLeft_B,CSRight_R,CSRight_G,CSRight_B,PosX,PosY,TM_State,Compass,Time,WheelLeft,WheelRight,LED_1,MyState);
    return info;
}
 
DLL_EXPORT char* GetTeamName()
{
     return "CoSpace Team";
}

DLL_EXPORT int GetCurAction()
{
    return CurAction;
}

//Only Used by CsBot Rescue Platform
DLL_EXPORT int GetTeleport()
{
    return Teleport;
}

//Only Used by CsBot Rescue Platform
DLL_EXPORT void SetSuperObj(int X, int Y, int num)
{
    SObj_X = X;
    SObj_Y = Y;
    SObj_Num = num;
}
//Only Used by CsBot Rescue Platform
DLL_EXPORT void GetSuperObj(int *X, int *Y, int *num)
{
    *X = SObj_X;
    *Y = SObj_Y;
    *num = SObj_Num;
}
//Used by CoSpace Rescue Simulation. 
///Called each time frame by CoSpaceRobot Studio to update the other robot information.
DLL_EXPORT void UpdateRobInfo(int sms, int X, int Y)
{
	OtherRob_SMS = sms;
	OtherRob_PosX = X;
	OtherRob_PosY = Y;
}

//Used by CsBot Rescue Platform
DLL_EXPORT void UpdateObjectInfo(int X, int Y, int state, int Dur)
{
	ObjState = state;
	ObjPosX = X;
	ObjPosY = Y;
	ObjDur = Dur;
}
DLL_EXPORT int GetMySMS()
{
	return MySMS;
}

#endif ////CSBOT_REAL

DLL_EXPORT void SetDataAI(volatile int* packet, volatile int *AI_IN)
{

    int sum = 0;

    USFront = AI_IN[0]; packet[0] = USFront; sum += USFront;
    USLeft = AI_IN[1]; packet[1] = USLeft; sum += USLeft;
    USRight = AI_IN[2]; packet[2] = USRight; sum += USRight;
    CSLeft_R = AI_IN[3]; packet[3] = CSLeft_R; sum += CSLeft_R;
    CSLeft_G = AI_IN[4]; packet[4] = CSLeft_G; sum += CSLeft_G;
    CSLeft_B = AI_IN[5]; packet[5] = CSLeft_B; sum += CSLeft_B;
    CSRight_R = AI_IN[6]; packet[6] = CSRight_R; sum += CSRight_R;
    CSRight_G = AI_IN[7]; packet[7] = CSRight_G; sum += CSRight_G;
    CSRight_B = AI_IN[8]; packet[8] = CSRight_B; sum += CSRight_B;
    PosX = AI_IN[9]; packet[9] = PosX; sum += PosX;
    PosY = AI_IN[10]; packet[10] = PosY; sum += PosY;
    TM_State = AI_IN[11]; packet[11] = TM_State; sum += TM_State;
    Compass = AI_IN[12]; packet[12] = Compass; sum += Compass;
    Time = AI_IN[13]; packet[13] = Time; sum += Time;
    packet[14] = sum;

}
DLL_EXPORT void GetCommand(int *AI_OUT)
{
    AI_OUT[0] = WheelLeft;
    AI_OUT[1] = WheelRight;
    AI_OUT[2] = LED_1;
    AI_OUT[3] = MyState;
}
void TurnTo(int curRot, int targetRot)
{
    int p0 = targetRot;
    int p3 = (targetRot + 3) % 360;
    int p15 = (targetRot + 15) % 360;
    int n3 = (targetRot - 3 + 360) % 360;
    int n15 = (targetRot - 15 + 360) % 360;
    int p180 = (targetRot + 180) % 360;
    int l = 0, r = 0;
    Dur = 6;
    //Within(-3,+3)deg, stop turing.
    l = n3; r = p3;
    if ((l < r && curRot > l && curRot < r) ||
    (l > r && (curRot > l || curRot < r)))
    {
        WheelLeft = 0;
        WheelRight = 0;
        Dur = 0;
        return;
    }
    //Within[3,15]deg,Turn Slowly
    l = p3; r = p15;
    if ((l < r && curRot >= l && curRot <= r) ||
        (l > r && (curRot >= l || curRot <= r)))
    {
        WheelLeft = 10;
        WheelRight = -10;
        return;
    }
    //Within[15,180]deg,Turn Faast
    l = p15; r = p180;
    if ((l < r && curRot >= l && curRot <= r) ||
       (l > r && (curRot >= l || curRot <= r)))
    {
        WheelLeft = 30;
        WheelRight = -30;
        return;
    }
    //Within[-15,-3]deg,Turn Slowly
    l = n15; r = n3;
    if ((l < r && curRot >= l && curRot <= r) ||
    (l > r && (curRot >= l || curRot <= r)))
    {
        WheelLeft = -10;
        WheelRight = 10;
        return;
    }
    //Within[-180,-15]deg,Turn Fast
    l = p180; r = n15;
    if ((l < r && curRot >= l && curRot <= r) ||
    (l > r && (curRot >= l || curRot <= r)))
    {
        WheelLeft = -30;
        WheelRight = 30;
        return;
    }
}
void GetEvent(int SuperDuration , int Duration , int EventNum)
{
    SupDur = SuperDuration;
    Dur = Duration;
    CurAction = EventNum;
}
void DoAction(int rightWheel , int leftWheel , int led)
{
    WheelRight = rightWheel;
    WheelLeft = leftWheel;
    LED_1 = led;
}
void Game0()
{
    if(SupDur > 0)
        SupDur --;
    else if(Dur > 0)
        Dur --;
    else
        GetEvent(0,10,1);

    switch(CurAction)
    {
        case 1:
            DoAction(60,60,0);
            break;
        default:
            break;
    }

}
void Game1()
{

}
DLL_EXPORT void OnTimer()
{
    switch (CurGame)
    {
        case 0:
            Game0();
            break;
        case 9:
            break;
        case 10:
            WheelLeft=0;
            WheelRight=0;
            LED_1=0;
            MyState=0;
            break;
        default:
            break;
    }
}

