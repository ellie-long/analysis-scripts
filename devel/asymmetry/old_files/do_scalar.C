void do_scalar(int RunL, int RunR)
{
        if(RunL<0 || RunL>=20000)
         cout << "Please choose L-arm run !!!!!!!!!!!!!!!!!!!!!!" << endl;
        else
        replay_scalar(RunL, 2100000);

        if(RunR<0 || RunR<=20000)
         cout << "Please choose R-arm run !!!!!!!!!!!!!!!!!!!!!!!" << endl;
        else
        replay_scalar(RunR, 2100000);

        ScalarStat(RunL, RunR, 3);
}

