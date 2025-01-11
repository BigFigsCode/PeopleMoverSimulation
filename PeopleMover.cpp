//SOLUTION
//  Program to simulate a "people mover" system.

#include <iostream>
#include <cstdlib>

using namespace std;

struct Segment
{
    int train; // +1, -1, or 0
    Segment* next;
    Segment* previous;
    Segment* next_adjacent;
    Segment* previous_adjacent;
};

const int TRACKS = 2;
const int SEGMENTS_PER_TRACK = 10;
const int TRAINS = 4;
const int MOVES = 20;

Segment* segments[TRACKS][SEGMENTS_PER_TRACK];

void initialize()
{
    for (int i = 0; i < TRACKS; i++)
    {
        for (int j = 0; j < SEGMENTS_PER_TRACK; j++)
        {
            segments[i][j] = new Segment;
        }
    }

    for (int i = 0; i < TRACKS; i++)
    {
        for (int j = 0; j < SEGMENTS_PER_TRACK; j++)
        {
            int jnext = (j + 1) % SEGMENTS_PER_TRACK;
            int jprev = (j + SEGMENTS_PER_TRACK - 1) % SEGMENTS_PER_TRACK;
            segments[i][j]->next = segments[i][jnext];
            segments[i][j]->previous = segments[i][jprev];
            segments[i][j]->next_adjacent = segments[TRACKS - 1 - i][jnext];
            segments[i][j]->previous_adjacent = segments[TRACKS - 1 - i][jprev];
        }
    }

    int count = 0;
    while (count < TRAINS)
    {
        int i = rand() % 2;
        int j = rand() % 10;
        if (segments[i][i]->train == 0)
        {
            // set the direction to clockwise (+1)  or counter-clockwise(-1)
            segments[i][j]->train = 1 - 2 * rand() % 2;
            count++;
        }
    }
}

void move()
{
    // In this loop, we set the moved trains to 2 or -2 so that
    // they don't get moved again if a later loop iteration sees them
    for (int i = 0; i < TRACKS; i++)
    {
        for (int j = 0; j < SEGMENTS_PER_TRACK; j++)
        {
            Segment* segment = segments[i][j];
            if (segment->train == 1)
            {
                if (segment->next->train == 0)
                {
                    segment->train = 0;
                    segment->next->train = 2;
                }
                else if (segment->next_adjacent->train == 0)
                {
                    segment->train = 0;
                    segment->next_adjacent->train = 2;
                }
                // else both adjacent spots are occupied
            }
            else if (segment->train == -1)
            {
                if (segment->previous->train == 0)
                {
                    segment->train = 0;
                    segment->previous->train = -2;
                }
                else if (segment->previous_adjacent->train == 0)
                {
                    segment->train = 0;
                    segment->previous_adjacent->train = -2;
                }
                // else both adjacent spots are occupied
            }
        }
    }

    for (int i = 0; i < TRACKS; i++)
    {
        for (int j = 0; j < SEGMENTS_PER_TRACK; j++)
        {
            int train = segments[i][j]->train;
            if (train == 2 || train == -2)
            {
                segments[i][j]->train = train / 2;
            }
        }
    }
}

void print()
{
    cout << "+-";
    for (int i = 0; i < SEGMENTS_PER_TRACK / 2; i++)
    {
        if (segments[0][i]->train == -1)
        {
            cout << "-<-";
        }
        else if (segments[0][i]->train == 1)
        {
            cout << "->-";
        }
        else
        {
            cout << "---";
        }
    }
    cout << "-+" << endl;
    cout << "|  x  x  x  x  x  |" << endl << "| ";
    for (int i = 0; i < SEGMENTS_PER_TRACK / 2; i++)
    {
        if (segments[1][i]->train == -1)
        {
            cout << "-<-";
        }
        else if (segments[1][i]->train == 1)
        {
            cout << "->-";
        }
        else
        {
            cout << "---";
        }
    }

    cout << " |" << endl << "| |             | |" << endl << "| ";
    for (int i = SEGMENTS_PER_TRACK - 1; i >= SEGMENTS_PER_TRACK / 2; i--)
    {
        if (segments[1][i]->train == -1)
        {
            cout << "->-";
        }
        else if (segments[1][i]->train == 1)
        {
            cout << "-<-";
        }
        else
        {
            cout << "---";
        }
    }
    cout << " |" << endl;
    cout << "|  x  x  x  x  x  |" << endl << "+-";
    for (int i = SEGMENTS_PER_TRACK - 1; i >= SEGMENTS_PER_TRACK / 2; i--)
    {
        if (segments[0][i]->train == -1)
        {
            cout << "->-";
        }
        else if (segments[0][i]->train == 1)
        {
            cout << "-<-";
        }
        else
        {
            cout << "---";
        }
    }
    cout << "-+" << endl << endl;
}

int main()
{
    initialize();
    print();
    for (int i = 1; i <= MOVES; i++)
    {
        move();
        print();
    }
    return 0;
}




