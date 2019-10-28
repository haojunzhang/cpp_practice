#include <iostream>
#include <string>
using namespace std;

class MediaPlayer
{
    // 宣告回呼函式的原型;
    typedef void (*OnMediaPlayCompleted)();

    // 宣告一個回呼函式指標;
    OnMediaPlayCompleted mOnMediaPlayCompleted;

public:
    MediaPlayer()
    {
        mOnMediaPlayCompleted = NULL;
    }

    void setOnMediaPlayCompleted(OnMediaPlayCompleted onMediaPlayCompleted)
    {
        mOnMediaPlayCompleted = onMediaPlayCompleted;
    }

    void play()
    {
        // playing1
        // playing2
        // playing3

        // completed
        (*mOnMediaPlayCompleted)();
    }
};

void onMediaPlayCompleted()
{
    cout << "onMediaPlayCompleted" << endl;
}
int main(int argc, char *argv[])
{
    MediaPlayer media_player;
    media_player.setOnMediaPlayCompleted(onMediaPlayCompleted);
    media_player.play();
    cout << "main running" << endl;
    return 0;
}