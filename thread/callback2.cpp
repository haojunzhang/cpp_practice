#include <iostream>
#include <string>
#include <thread>
#include <chrono>
using namespace std;

void sleep(int milliseconds)
{
    this_thread::sleep_for(chrono::milliseconds(milliseconds));
}

class AsyncTask
{
private:
    typedef void (*OnPreExecute)();
    OnPreExecute mOnPreExecute;

    typedef void (*OnProgressUpdate)(string text);
    OnProgressUpdate mOnProgressUpdate;

    typedef void (*DoInBackground)();
    DoInBackground mDoInBackground;

    typedef void (*OnPostExecute)();
    OnPostExecute mOnPostExecute;

public:
    void setOnPreExecute(OnPreExecute mOnPreExecute)
    {
        this->mOnPreExecute = mOnPreExecute;
    }
    void setOnProgressUpdate(OnProgressUpdate mOnProgressUpdate)
    {
        this->mOnProgressUpdate = mOnProgressUpdate;
    }
    void setDoInBackground(DoInBackground mDoInBackground)
    {
        this->mDoInBackground = mDoInBackground;
    }
    void setOnPostExecute(OnPostExecute mOnPostExecute)
    {
        this->mOnPostExecute = mOnPostExecute;
    }

    void execute()
    {
        (*mOnPreExecute)();
        (*mDoInBackground)();
        sleep(1000);
        (*mOnProgressUpdate)("1/3");
        sleep(1000);
        (*mOnProgressUpdate)("2/3");
        sleep(1000);
        (*mOnProgressUpdate)("3/3");
        (*mOnPostExecute)();
    }
};

void onPreExecute()
{
    cout << "onPreExecute" << endl;
}

void onProgressUpdate(string text)
{
    cout << "onProgressUpdate:" << text << endl;
}

void onDoInBackground()
{
    cout << "onDoInBackground" << endl;
}

void onPostExecute()
{
    cout << "onPostExecute" << endl;
}

void downloadFile()
{
    AsyncTask mAsyncTask;
    mAsyncTask.setOnPreExecute(onPreExecute);
    mAsyncTask.setOnProgressUpdate(onProgressUpdate);
    mAsyncTask.setDoInBackground(onDoInBackground);
    mAsyncTask.setOnPostExecute(onPostExecute);
    mAsyncTask.execute();
}

int main()
{

    thread mThread(downloadFile);

    mThread.join();

    return 0;
} // clang++ callback2.cpp