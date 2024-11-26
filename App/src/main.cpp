// Selected Tasks:

// Image Processing Application
// Archiving Application

// Tools Used:

// C++
// CMake
// Qt Widgets
// Description:
// My idea was to create a single application that integrates both tasks into one program.

// Image Processing:
// The implementation went smoothly for the most part. I implemented image loading functionality,
// added the ability to modify the image, and included an option to save it.

// Archiving:
// This task was more challenging for me, as I had no prior experience with it.
// Understanding the intricacies of this process turned out to be quite a challenge.
// The biggest issue arose when I decided to use the Boost library for implementation. There were
// numerous specific requirements for working with ZLib. Ultimately, I couldn't integrate the Boost
// library into the project and compile it due to time constraints.

// Platform Consideration:
// I understand that the task description suggested using Linux, but since I was working on my
// personal computer,
//  installing Linux was not feasible. Therefore, I decided to use cross-platform tools for
//  development.

// Reflection:
// I am very grateful for the opportunity to work on this task. It was truly interesting and gave me
// a chance to prove myself. Despite the challenges, I will continue working on this task to gain a
// deeper understanding of this topic.

#include "MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();

    return app.exec();
}
