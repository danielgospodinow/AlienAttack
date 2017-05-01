#include "game_utilities.hpp"

TTF_Font* GameUtilities::_font = NULL;
int GameUtilities::_score = 0;
const char* GameUtilities::_highScoresFilePath = "data/highscores.txt";
int GameUtilities::_highScores[globals::MAX_HIGHSCORES] = {0};

void GameUtilities::init()
{
    _font = TTF_OpenFont("fonts/raidercrusader.ttf", 24);
    readHighScores();
}

void GameUtilities::close()
{
    TTF_CloseFont(_font);
}

void GameUtilities::renderText(SDL_Texture* texture, SDL_Rect rect, Vec2<int> offset)
{
    rect.x += offset.x;
    rect.y += offset.y;
    SDL_RenderCopy(SDL_Components::getRenderer(), texture, NULL, &rect);
}

int GameUtilities::getStrLen(const char *str)
{
    int lenght = 0;
    while(*str)
    {
        lenght += 1;
        str += 1;
    }
    return lenght;
}

int GameUtilities::getRandomNumber(int startRange, int endRange)
{
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(startRange, endRange);

    return distr(eng);
}

bool GameUtilities::areColliding(SDL_Rect one, SDL_Rect two)
{
    if(!(one.x <= two.x))
    {
        SDL_Rect temp = one;
        one = two;
        two = temp;
    }

    if((one.x + one.w > two.x) && (two.y + two.h >= one.y && two.y < one.y + one.h))
        return true;
    return false;
}

void GameUtilities::readHighScores()
{
    ifstream highScoresFile (_highScoresFilePath /*,ios::in*/ );

    if(!highScoresFile.is_open())
    {
        cout << "Problem opening highscores file";
        return;
    }

    int iter = 0;
    while(iter < globals::MAX_HIGHSCORES && highScoresFile >> _highScores[iter++]);

    selectionSort(_highScores, globals::MAX_HIGHSCORES);

    highScoresFile.close();
}

void GameUtilities::writeHighScores()
{
    ofstream highScoresFile (_highScoresFilePath, ios::out | ios::trunc);

    if(!highScoresFile.is_open())
    {
        cout << "Problem opening highscores file";
        return;
    }

    for(int i=0; i<globals::MAX_HIGHSCORES; i++)
        highScoresFile << _highScores[i] << "\n";
}

void GameUtilities::updateHighScores()
{
    if(_score < _highScores[globals::MAX_HIGHSCORES - 1])
        return;

    for(int i=0; i<globals::MAX_HIGHSCORES; i++) //insertion algorithm
    {
        if(_score > _highScores[i])
        {
            for(int j=globals::MAX_HIGHSCORES - 1; j>i; j--)
                _highScores[j] = _highScores[j - 1];

            _highScores[i] = _score;
            break;
        }
    }

    writeHighScores();
}

TTF_Font* const GameUtilities::getFont() {return _font;}
int GameUtilities::getScore() {return _score;}
void GameUtilities::setScore(int score) {_score = score;}

template <typename T>
void GameUtilities::selectionSort(T* arr, int size)
{
    for(int i=0; i<size - 1; i++)
    {
        int maxIndex = i;

        for(int j=i + 1; j<size; j++)
            if(arr[j] > arr[maxIndex])
                maxIndex = j;

        swap(arr[i], arr[maxIndex]);
    }
}

template <typename T>
void GameUtilities::swap(T& one, T& two)
{
    T temp = one;
    one = two;
    two = temp;
}

int* GameUtilities::getHighscores()
{
    return _highScores;
}
