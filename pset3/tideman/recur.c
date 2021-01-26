bool check_cycle(bool locked[][], int candidates)
{
    if (x == candidates)
    {
        if (locked[candidates][0] == true)
            return true;
    }



    for (int i = 0; i < candidates; i++)
    {
        if (locked[candidates][i] == true)
        {
            check_cycle(locked, candidates - 1);
        }
    }

}
int check = 0;

bool check_cycle(int x, int y)
{
    if (x == y)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[x][i] == true)
        {
            check_cycle(i);
        }
        else
        {
            return false;
        }
    }
}


bool check_cycle(int x)
{
    int checkcycle = 0;
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < x; j++)
        {
            if (locked[j][i] == true)
            {
                checkcycle++;
                break;
            }
        }
    }
    if (checkcycle == candidate_count)
    {
        return true;
    }
    else
    {
        return false;
    }
}