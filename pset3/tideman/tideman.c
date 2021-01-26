#include <cs50.h>
#include <stdio.h>
#include <string.h>

bool check_cycle(int x, int y);

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        // If the vote is valid records it in the ranks[] array
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Goes through all the candidates and compares them with all other candidates updating preferences
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i == j)
            {
                preferences[i][j] = 0;
            }
            else
            {
                for (int k = 0; k < candidate_count; k++)
                {
                    if (ranks[k] == i)
                    {
                        preferences[i][j]++;
                        break;
                    }

                    else if (ranks[k] == j)
                    {
                        break;
                    }
                }
            }
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // If one candidate has more votes than another a pair is created
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            // All pairs are selection sorted base on the strenght of their victory
            if ((preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner]) >
                (preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner]))
            {
                pair temp[MAX * (MAX - 1) / 2]; // This array stores the values of one of the pair being switched
                temp[i] = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp[i];
            }
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!check_cycle(pairs[i].loser, pairs[i].winner)) // If the new pair doesn't generate a loop it is locked
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    int checkwin = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                checkwin++;
            }
        }

        if (checkwin == 0)
        {
            printf("%s\n", candidates[i]);
            break;
        }
        else
        {
            checkwin = 0;
        }
    }
}

bool check_cycle(int x, int y) // A recursive function that checks if any new pair would generate a loop and return true if it does
{
    if (x == y)
    {
        return true;
    }
    else
    {
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[x][i] == true)
            {
                return check_cycle(i, y);
            }

        }
    }
    return false;
}
