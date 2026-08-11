/*
 * Group Members:
 * Ayal Yakobe (amy2127)
 * Leen Alshorafa (laa2202)
 * Aashir Khan (ak5445)
 *
 * Group Number 8
 *
 * BFS reference:
 * MIT OpenCourseWare, 6.006 Introduction to Algorithms,
 * Recitation 15: Shortest Paths.
 * https://ocw.mit.edu/courses/6-006-introduction-to-algorithms-fall-2011/resources/recitation-15-shortest-paths/
 *
 * Parent/path reconstruction reference:
 * Stack Overflow, "How does a Breadth-First Search work when looking for Shortest Path?"
 * https://stackoverflow.com/questions/8379785/how-does-a-breadth-first-search-work-when-looking-for-shortest-path
 */

#include <cctype>
#include <iostream>
#include <limits>
#include <queue>
#include <string>
#include <vector>

using namespace std;

const int NOT_VISITED = -1;
const int MAX_LIMIT = 20000000;

// Checks that the input is made only of digits.
bool isValidNumber(string input)
{
    if (input.length() == 0)
    {
        return false;
    }

    for (int i = 0; i < (int)input.length(); i++)
    {
        if (!isdigit(input[i]))
        {
            return false;
        }
    }

    return true;
}

// Converts the string into a number.
// If it is too large for long long, return -1 so we can reject it safely.
long long stringToNumber(string input)
{
    long long number = 0;

    for (int i = 0; i < (int)input.length(); i++)
    {
        int digit = input[i] - '0';

        if (number > (numeric_limits<long long>::max() - digit) / 10)
        {
            return -1;
        }

        number = number * 10 + digit;
    }

    return number;
}

bool isPowerOfTwo(long long number)
{
    if (number < 1)
    {
        return false;
    }

    while (number > 1)
    {
        if (number % 2 != 0)
        {
            return false;
        }
        number /= 2;
    }

    return true;
}

string makePowerOfTwoExpression(long long target)
{
    string answer = "1";

    while (target > 1)
    {
        answer += " x 2";
        target /= 2;
    }

    return answer;
}

string makeExpression(int target, vector<int>& parent, vector<char>& moveUsed)
{
    vector<char> moves;
    int current = target;

    // The BFS remembers the previous number for each number it reaches.
    // Starting from the target, we can follow parent[] backward until we get
    // to 1, which gives us the path for the expression.
    while (current != 1)
    {
        moves.push_back(moveUsed[current]);
        current = parent[current];
    }

    string answer = "1";

    // The path was collected backward, so we print the moves in reverse order.
    for (int i = (int)moves.size() - 1; i >= 0; i--)
    {
        if (moves[i] == 'D')
        {
            answer += " / 3";
        }
        else
        {
            answer += " x 2";
        }
    }

    return answer;
}

bool bfs(int target, int limit, string& answer)
{
    // parent[x] stores the number that came before x.
    // moveUsed[x] stores which operation was used to reach x.
    vector<int> parent(limit + 1, NOT_VISITED);
    vector<char> moveUsed(limit + 1, ' ');
    queue<int> q;

    // The assignment says every expression starts with 1.
    parent[1] = 1;
    q.push(1);

    // BFS uses a queue, so numbers reached in fewer moves are checked first.
    // That is what makes the expression shortest.
    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        if (current == target)
        {
            answer = makeExpression(target, parent, moveUsed);
            return true;
        }

        // Try division first, because the instructions say to build solutions
        // with division before multiplication.
        int next = current / 3;
        if (parent[next] == NOT_VISITED)
        {
            parent[next] = current;
            moveUsed[next] = 'D';
            q.push(next);
        }

        // Multiplication is tried second. The limit check keeps next inside
        // the vector so we do not go out of bounds.
        if (current <= limit / 2)
        {
            next = current * 2;
            if (parent[next] == NOT_VISITED)
            {
                parent[next] = current;
                moveUsed[next] = 'M';
                q.push(next);
            }
        }
    }

    return false;
}

string findExpression(int target)
{
    if (target == 1)
    {
        return "1";
    }

    int limit = 1024;

    // Some targets need the expression to go higher than the target first and
    // then come back down using division. If the first limit is not enough, the
    // limit grows and BFS is tried again.
    while (limit < target && limit <= MAX_LIMIT / 2)
    {
        limit *= 2;
    }

    while (limit <= MAX_LIMIT)
    {
        string answer;

        if (bfs(target, limit, answer))
        {
            return answer;
        }

        if (limit == MAX_LIMIT)
        {
            break;
        }
        else if (limit > MAX_LIMIT / 2)
        {
            limit = MAX_LIMIT;
        }
        else
        {
            limit *= 2;
        }
    }

    return "";
}

int main(int argc, char* argv[])
{
    // The program needs exactly one command line argument.
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <non-negative integer>" << endl;
        return 0;
    }

    string input = argv[1];

    // Check for bad input before doing the math part.
    if (!isValidNumber(input))
    {
        cout << "Error: Argument '" << input << "' is not a non-negative integer." << endl;
        return 0;
    }

    long long target = stringToNumber(input);

    if (target == -1)
    {
        cout << "No solution found." << endl;
        return 0;
    }

    // Powers of two are easy because they only need repeated multiplication.
    // This also handles large powers of two without using the BFS arrays.
    if (target > MAX_LIMIT && isPowerOfTwo(target))
    {
        cout << makePowerOfTwoExpression(target) << endl;
        return 0;
    }

    // This keeps the BFS from using too much memory on other very large inputs.
    if (target > MAX_LIMIT)
    {
        cout << "No solution found." << endl;
        return 0;
    }

    string answer = findExpression((int)target);

    if (answer == "")
    {
        cout << "No solution found." << endl;
    }
    else
    {
        cout << answer << endl;
    }

    return 0;
}
