#include <iostream>
#include <string>

using namespace std;

class FootballTeam
{
    string name;
    int goals;
    int points;

public:
    FootballTeam()
    {
        name = "team";
        goals = 0;
        points = 0;
    }
    FootballTeam(string name, int goals, int points)
    {
        this->name = name;
        this->goals = goals;
        this->points = points;
    }
    void DisplayStatus()
    {
        cout << "Team name: " << this->name << endl;
        cout << "Goals: " << this->goals << "\nPoints: " << this->points << endl;
        cout << "-----------------------------" << endl;
    }
    bool scoreGoal()
    {
        this->goals++;
        return true;
    }
    bool AddPoints(int points)
    {
        this->points += points;
        return true;
    }
    void setName(string name)
    {
        this->name = name;
    }
    ~FootballTeam()
    {
        cout << "Team " << this->name << " was eliminated..." << endl;
    }
    int operator+(FootballTeam &team2)
    {
        return team2.points + this->points;
    }
    friend void compareGoals(FootballTeam &team1, FootballTeam &team2);
};

void compareGoals(FootballTeam &team1, FootballTeam &team2)
{
    if (team1.goals > team2.goals)
        cout << "Team " << team1.name << " wins!" << endl;
    else if (team1.goals < team2.goals)
        cout << "Team " << team2.name << " wins!" << endl;
    else
    {
        cout << "Draw" << endl;
    }
}

int main()
{
    FootballTeam team1("Team A", 3, 10);
    FootballTeam team2("Team B", 5, 12);
    cout << "Team 1 status: " << endl;
    team1.DisplayStatus();
    cout << "Team 2 status: " << endl;
    team2.DisplayStatus();

    team1.scoreGoal();
    team2.AddPoints(3);

    cout << "Team 1 status: " << endl;
    team1.DisplayStatus();
    cout << "Team 2 status: " << endl;
    team2.DisplayStatus();

    cout << "Total points of both teams: " << team1 + team2 << endl;

    compareGoals(team1, team2);
}