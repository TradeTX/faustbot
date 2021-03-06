//
// Created by Evan Kirkiles on 7/21/18.
//

#include "window.hpp"

// Constructor for the Bot's main window
BotWindow::BotWindow(QWidget *parent) : QWidget(parent) {
    // Set the size of the window
    setFixedSize(1100, 650);
    // Set the stylesheet for the window
    QFile File(file_paths::STYLESHEET);
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    QFile File2(QApplication::applicationDirPath().append(file_paths::COLORSTYLESHEET).toStdString().c_str());
    File2.open(QFile::ReadOnly);
    QString CStyleSheet = QLatin1String(File2.readAll());
    setStyleSheet(StyleSheet + CStyleSheet);
    // Finally, set some various window attributes
    setAttribute(Qt::WA_QuitOnClose);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowTitle(tr("FAUST BOT"));
    setObjectName("main_window");

    // Create URLAndMethod metatype
    qRegisterMetaType<URLAndMethod>("URLAndMethod");

    // Build the Dark Title Bar
    dtb = new DarkTitleBar(this, true);

    // SIZE POLICIES
    // Size policies for top row
    QSizePolicy spRight(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spRight.setHorizontalStretch(3);

    // LAYOUTS
    // Create two vertical layouts within a horizontal main layout
    auto externLayout = new QVBoxLayout;
    externLayout->setContentsMargins(0, 0, 0, 0);
    auto inFrameLayout = new QVBoxLayout;
    inFrameLayout->setContentsMargins(0, 0, 0, 0);
    auto bg = new QFrame(this);
    bg->setObjectName("main_window");
    bg->setLayout(inFrameLayout);
    inFrameLayout->addWidget(dtb);
    auto mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(11, 3, 11, 11);
    auto topLayout = new QHBoxLayout;
    auto botLayout = new QHBoxLayout;
    // Vertical layouts for the top layout
    auto leftColumn = new QVBoxLayout;
    auto alltaskButtonsLayout = new QHBoxLayout;
    auto bottomHorLayout = new QHBoxLayout;
    bottomHorLayout->setContentsMargins(0, 0, 0, 0);
    bottomHorLayout->setSizeConstraint(QLayout::SetMinimumSize);
    auto rightColumn = new QVBoxLayout;
    // Horizontal layout that goes above the listview
    auto tasktitleRow = new QHBoxLayout;
    // Vertical layout for the listview widget
    tasklistLayout = new QVBoxLayout;
    // Combine layouts
    container = new QWidget(this);
    container->setContentsMargins(0, 0, 0, 0);
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(botLayout);
    container->setLayout(mainLayout);
    topLayout->addLayout(leftColumn);
    topLayout->setStretchFactor(leftColumn, 1);
    inFrameLayout->addWidget(container);
    externLayout->addWidget(bg);
    setLayout(externLayout);

    // WIDGETS
    // Left column widgets
    QImage img(file_paths::LOGO_FILE);
    QPixmap logoimg;
    logoimg = QPixmap::fromImage(img).scaled(420, 400, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    logoimg.setDevicePixelRatio(2.0);
    logo = new QLabel();
    logo->setPixmap(logoimg);
    logo->setFixedSize(210, 200);
    title = new QLabel("FAUST BOT", container);
    title->setAlignment(Qt::AlignCenter);
    title->setObjectName("bot_title");
    title->setFixedHeight(30);
    startAllTasks = new QPushButton("Start All", container);
    startAllTasks->setObjectName("startallbutton");
    stopAllTasks = new QPushButton("Stop All", container);
    stopAllTasks->setObjectName("stopallbutton");
    alltaskButtonsLayout->addWidget(startAllTasks);
    alltaskButtonsLayout->addWidget(stopAllTasks);
    addtask = new QPushButton("NEW KEYWORD TASK", container);
    addtask->setObjectName("addtaskbutton");
    addtask->setFixedHeight(70);
    addVIDtask = new QPushButton("NEW VARIANT ID TASK", container);
    addVIDtask->setObjectName("addtaskbuttonv2");
    addVIDtask->setFixedHeight(50);
    variantParser = new QPushButton("Parser", container);
    variantParser->setObjectName("sidebuttons");
    billing = new QPushButton("Profiles", container);
    billing->setObjectName("sidebuttons");
    proxies = new QPushButton("Proxies", container);
    proxies->setObjectName("sidebuttons");
    clear = new QPushButton("Clear", container);
    clear->setObjectName("sidebuttons");
    clear->setStyleSheet("margin-top: 0px; margin-bottom: 0px;");
    saveTasks = new QPushButton(container);
    saveTasks->setObjectName("sidebuttons");
    saveTasks->setFixedSize(32, 30);
    saveTasks->setIcon(QIcon(file_paths::UPLOAD_IMG));
    saveTasks->setStyleSheet("margin-top: 0px; margin-bottom: 0px;");
    loadTasks = new QPushButton(container);
    loadTasks->setObjectName("sidebuttons");
    loadTasks->setFixedSize(32, 30);
    loadTasks->setIcon(QIcon(file_paths::DOWNLOAD_IMG));
    loadTasks->setStyleSheet("margin-top: 0px; margin-bottom: 0px;");
    settings = new QPushButton(container);
    settings->setObjectName("sidebuttons");
    settings->setFixedSize(32, 30);
    settings->setIcon(QIcon(file_paths::GEAR_IMG));
    settings->setStyleSheet("margin-top: 0px; margin-bottom: 0px;");
    bottomHorLayout->addWidget(clear);
    bottomHorLayout->addSpacing(5);
    bottomHorLayout->addWidget(saveTasks);
    bottomHorLayout->addSpacing(5);
    bottomHorLayout->addWidget(loadTasks);
    bottomHorLayout->addSpacing(5);
    bottomHorLayout->addWidget(settings);
    copyrightLabel = new QLabel("© 2018 Faust BOT - All Rights Reserved", container);
    copyrightLabel->setObjectName("copyrightlabel");
    // Add widgets to the left column
    leftColumn->addWidget(logo);
    leftColumn->addWidget(title);
    leftColumn->addLayout(alltaskButtonsLayout);
    leftColumn->addWidget(addtask);
    leftColumn->addWidget(addVIDtask);
    leftColumn->addWidget(variantParser);
    leftColumn->addWidget(billing);
    leftColumn->addWidget(proxies);
    leftColumn->addLayout(bottomHorLayout);
    leftColumn->addWidget(copyrightLabel);
    leftColumn->setAlignment(Qt::AlignTop);

    // Right column widget
    line1 = new QFrame();
    line1->setFrameShape(QFrame::HLine);
    line1->setFrameShadow(QFrame::Sunken);
    line1->setObjectName("horizontal_line");
    line2 = new QFrame();
    line2->setFrameShape(QFrame::HLine);
    line2->setFrameShadow(QFrame::Sunken);
    line2->setObjectName("horizontal_line");
    tasktitle = new QLabel("TASKS", container);
    tasktitle->setAlignment(Qt::AlignCenter);
    tasktitle->setObjectName("task_title");
    tasklist = new QScrollArea(container);
    tasklist->setSizePolicy(spRight);
    tasklist->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tasklist->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tasklistwidget = new QWidget(container);

    tasklistLayout->setAlignment(Qt::AlignTop);
    tasklistwidget->setLayout(tasklistLayout);
    tasklistwidget->setObjectName("scrollarea");
    tasklist->setWidget(tasklistwidget);
    tasklist->setWidgetResizable(true);
    // Add widget to the right column
    tasktitleRow->addWidget(line1);
    tasktitleRow->addWidget(tasktitle);
    tasktitleRow->addWidget(line2);
    rightColumn->addLayout(tasktitleRow);
    rightColumn->addWidget(tasklist);
    topLayout->addLayout(rightColumn);
    topLayout->setStretchFactor(rightColumn, 4);

    // Open the add task window when the add task button is clicked
    connect(addtask, SIGNAL(clicked()), this, SLOT(openNewTask()));
    // Open the add VID task window when the add VID task buton is clicked
    connect(addVIDtask, SIGNAL(clicked()), this, SLOT(openNewVIDTask()));
    // Open the parser window when the parser button is clicked
    connect(variantParser, SIGNAL(clicked()), this, SLOT(openParser()));
    // Open the profiles window when the profiles button is clicked
    connect(billing, SIGNAL(clicked()), this, SLOT(openProfiles()));
    // Open the proxies window when the proxies button is clicked
    connect(proxies, SIGNAL(clicked()), this, SLOT(openProxies()));
    // Open the settings window when the settings button is clicked
    connect(settings, SIGNAL(clicked()), this, SLOT(openSettings()));
    // Connect the task loader to its button
    connect(loadTasks, SIGNAL(clicked()), this, SLOT(loadInSavedTasks()));
    // Make the clear button emit the delete all tasks
    connect(clear, &QPushButton::clicked, [this] () { emit deleteAllTasks(); });
    // Clear the tasks cache file when you download
    connect(saveTasks, &QPushButton::clicked, [this] () { std::remove(QApplication::applicationDirPath().append(file_paths::TASKS_CACHE).toStdString().c_str()); });

    // Build the timer updated on second intervals
    timeChecker = new QTimer(container);
    connect(timeChecker, &QTimer::timeout, [this] () { emit timeUpdated(QDateTime::currentDateTime()); } );
    timeChecker->setInterval(1000);
    timeChecker->start();

    // Check the authentication of the window
    if (database::USE_AUTHENTICATION) { checkAuthentication(); }
}

// Checks the authentication
void BotWindow::checkAuthentication() {

    atp = new AuthenticationPopup();
    // Make sure not authenticated right off the bat
    if (atp->authenticated) {
        delete atp;
    } else {
        // Disable the container
        container->setEnabled(false);

        // Fade out the container
        auto *eff = new QGraphicsOpacityEffect(this);
        container->setGraphicsEffect(eff);
        QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
        a->setDuration(500);
        a->setStartValue(1);
        a->setEndValue(0.1);
        a->setEasingCurve(QEasingCurve::Linear);
        a->start(QPropertyAnimation::DeleteWhenStopped);
        connect(a, SIGNAL(finished()), this, SLOT(buildAuthWindow()));
    }
}

// Builds the authentication window
void BotWindow::buildAuthWindow() {
    atp->show();
    atp->setFocus();
    connect(atp, SIGNAL(closed()), this, SLOT(receiveAuthentication()));
}

// Receives the authentication, as the authentication window only closes when authenticated
void BotWindow::receiveAuthentication() {
    // Fade in the container
    auto *eff = new QGraphicsOpacityEffect(this);
    container->setGraphicsEffect(eff);
    QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
    a->setDuration(500);
    a->setStartValue(0.1);
    a->setEndValue(1);
    a->setEasingCurve(QEasingCurve::Linear);
    a->start(QPropertyAnimation::DeleteWhenStopped);

    // Enable the container again
    container->setEnabled(true);
}

// Slot which takes information from the new task window and builds a task
void BotWindow::buildTask(QString title, URLAndMethod website, QString collection,
                          QString keywords, QString colorKeywords, QString size,
                          QDateTime start, QString profile, QString proxy, int copies, int position) {

    // Gets an identifier by checking how many task widgets there are on the tasklist
    // Make sure to break the keywords QStrings down into its component keywords
    // Builds a task based on the number of copies sent
    for (int i=0; i<copies; i++) {
        addTask(title.toStdString(), website, std::to_string(numTasksCreated), collection.toStdString(),
                vectorFromString(keywords.toStdString()), vectorFromString(colorKeywords.toStdString()),
                size.toStdString(), start, profile.toStdString(), proxy.toStdString(), constants::BASE_NUMRESULTS,
                constants::BASE_FREQ, position);
    }
}

// Slot which takes information from the new VID task window and builds necessary VID tasks
void BotWindow::buildVIDTask(QString title, URLAndMethod website, QString variantID, QString variantName,
                             QString variantSize, QDateTime start, QString profile, QString proxy,
                             QString p_imageURL, int copies, int position) {

    // Gets an identifier by checking how many task widgets there are on the tasklist
    // Builds a task based on the number of copies sent
    for (int i = 0; i < copies; i++) {
        addVIDTaskFunc(title.toStdString(), website, std::to_string(numTasksCreated), variantID.toStdString(),
                       variantName.toStdString(), variantSize.toStdString(), start, profile.toStdString(),
                       proxy.toStdString(), p_imageURL, constants::BASE_FREQ, position);
    }
}

// Creates a task and adds it to the tasklist
void BotWindow::addTask(const std::string &title, const URLAndMethod &website, const std::string &identifier,
                        const std::string &collection, const std::vector<std::string> &keywords,
                        const std::vector<std::string> &colorKeywords, const std::string &size,
                        const QDateTime& startAt, const std::string& profile, const std::string& proxy,
                        unsigned int resultsToCheck, unsigned int frequency, int position) {

    // Increment the task identifier
    numTasksCreated++;

    // Create a new task
    auto newtask = new TaskWidget(title, website, identifier, collection, keywords, colorKeywords, size,
                                        startAt, profile, proxy, &logWindowOpen, &editWindowOpen,
                                        resultsToCheck, frequency, tasklistwidget);

    // Connect the signals of the window to this new task's start and stop
    connect(startAllTasks, SIGNAL(clicked()), newtask, SLOT(run()));
    connect(stopAllTasks, SIGNAL(clicked()), newtask, SLOT(stopWidget()));
    connect(saveTasks, SIGNAL(clicked()), newtask, SLOT(saveToFile()));

    // Connect the 1 second interval timer to the taskwidget's time check function
    connect(this, SIGNAL(timeUpdated(QDateTime)), newtask, SLOT(checkTime(QDateTime)));
    connect(this, SIGNAL(deleteAllTasks()), newtask, SLOT(exit()));

    // Connect the button's duplicate button to building the same task
    connect(newtask->duplicateButton, &ClickableImage::clicked, [this, newtask] () {
        buildTask(newtask->title->text(), newtask->task->swh.sourceURL, newtask->task->collection.c_str(),
                  stringFromVector(newtask->task->keywords).c_str(), stringFromVector(newtask->task->colorKeywords).c_str(),
                  newtask->task->size.c_str(), newtask->task->startat, newtask->task->profile.c_str(), newtask->task->proxy.c_str(),
                  1, tasklistLayout->indexOf(newtask) + 1);
    });


    // If the position is set, then insert the widget at that position
    if (position > 0) {
        tasklistLayout->insertWidget(position, newtask);
    } else {
        // Adds the task to the qvboxlayout
        tasklistLayout->addWidget(newtask);
    }
    // Show the new task
    newtask->show();
}

// Creates a task and adds it to the tasklist
void BotWindow::addVIDTaskFunc(const std::string &title, const URLAndMethod &website, const std::string &identifier,
                               const std::string &variantID, const std::string &variantName,
                               const std::string &variantSize, const QDateTime &startAt, const std::string &profile,
                               const std::string &proxy, QString p_imageURL, unsigned int frequency, int position) {

    // Increment the task identifier
    numTasksCreated++;

    // Create a new task
    auto newtask = new VIDTaskWidget(title, website, identifier, variantID, profile, proxy, startAt, variantName,
            variantSize, p_imageURL, &logWindowOpen, &editWindowOpen, frequency, tasklistwidget);

    // Connect the signals of the window to this new task's start and stop
    connect(startAllTasks, SIGNAL(clicked()), newtask, SLOT(run()));
    connect(stopAllTasks, SIGNAL(clicked()), newtask, SLOT(stopWidget()));
    connect(saveTasks, SIGNAL(clicked()), newtask, SLOT(saveToFile()));

    // Connect the 1 second interval timer to the taskwidget's time check function
    connect(this, SIGNAL(timeUpdated(QDateTime)), newtask, SLOT(checkTime(QDateTime)));
    connect(this, SIGNAL(deleteAllTasks()), newtask, SLOT(exit()));

    // Connect the button's duplicate button to building the same task
    connect(newtask->duplicateButton, &ClickableImage::clicked, [this, newtask] () {
        buildVIDTask(newtask->title->text(), newtask->task->swh.sourceURL, newtask->task->variantID.c_str(),
                     newtask->variantName->toPlainText(), newtask->variantSize->text(),
                     newtask->task->startat, newtask->task->profile.c_str(), newtask->task->proxy.c_str(),
                     newtask->imageURL, 1, tasklistLayout->indexOf(newtask) + 1);
    });

    // If the position is set, then insert the widget at that position
    if (position > 0) {
        tasklistLayout->insertWidget(position, newtask);
    } else {
        // Adds the task to the qvboxlayout
        tasklistLayout->addWidget(newtask);
    }
    // Show the new task
    newtask->show();

}

// Loads in the saved tasks from the tasks cache
void BotWindow::loadInSavedTasks() {

    // Clear all the tasks
    emit deleteAllTasks();

    // Open up the saved tasks file
    std::ifstream filein(QApplication::applicationDirPath().append(file_paths::TASKS_CACHE).toStdString().c_str());
    std::string str;

    // Now parse through the file and add each saved task
    while(getline(filein, str)) {
        // Do not consider empty lines
        if (str.empty()) { continue; }

        // The first 3 letters of the line denote what type of task is being added
        if (str.substr(0, 3) == "KWD") {
            str.erase(0, 4);

            // Get the title
            const unsigned long delimPos = str.find(" :-: ");
            std::string title = str.substr(0, delimPos);
            str.erase(0, delimPos + 5);

            // Now build a JSON object of the rest of the task
            QJsonDocument jsonDoc = QJsonDocument::fromJson(QString(str.c_str()).toUtf8());
            QJsonObject jsonObjecc = jsonDoc.object();

            // Build the task from the JSON
            addTask(title, supported_sites::WEBSITES.at(supported_sites::WEBSITES_BWD.at(jsonObjecc["website"].toString().toStdString())),
                    jsonObjecc["identifier"].toString().toStdString(), jsonObjecc["collection"].toString().toStdString(),
                    vectorFromString(jsonObjecc["keywords"].toString().toStdString()),
                    vectorFromString(jsonObjecc["colorKeywords"].toString().toStdString()),
                    jsonObjecc["size"].toString().toStdString(),
                    QDateTime::fromSecsSinceEpoch(stoi(jsonObjecc["startat"].toString().toStdString())),
                    jsonObjecc["profile"].toString().toStdString(),
                    jsonObjecc["proxy"].toString().toStdString(), constants::BASE_NUMRESULTS,
                    stoi(jsonObjecc["frequency"].toString().toStdString()));
        } else if (str.substr(0, 3) == "VID") {
            str.erase(0, 4);

            // Get the title
            const unsigned long delimPos = str.find(" :-: ");
            std::string title = str.substr(0, delimPos);
            str.erase(0, delimPos + 5);

            // Now build a JSON object of the rest of the task
            QJsonDocument jsonDoc = QJsonDocument::fromJson(QString(str.c_str()).toUtf8());
            QJsonObject jsonObjecc = jsonDoc.object();

            // Build the task from the JSON
            addVIDTaskFunc(title, supported_sites::WEBSITES.at(supported_sites::WEBSITES_BWD.at(jsonObjecc["website"].toString().toStdString())),
                           jsonObjecc["identifier"].toString().toStdString(),
                           jsonObjecc["variantID"].toString().toStdString(),
                           jsonObjecc["prodTitle"].toString().toStdString(),
                           jsonObjecc["variantSize"].toString().toStdString(),
                           QDateTime::fromSecsSinceEpoch(stoi(jsonObjecc["startat"].toString().toStdString())),
                           jsonObjecc["profile"].toString().toStdString(),
                           jsonObjecc["proxy"].toString().toStdString(),
                           jsonObjecc["variantImg"].toString(),
                           stoi(jsonObjecc["frequency"].toString().toStdString()));
        }
    }
}

// Opens the add task window
void BotWindow::openNewTask() {
    if (addTaskOpen) {
        // Shopw the currently open task window
        atd->raise();
        atd->setFocus();
        return;
    }

    // If there is a VID new task open, just close it
    if (addVIDTaskOpen) { avidtd->close(); }

    // Build the window if it does not exist, otherwise just show it
    atd = new AddTaskDisplay();
    atd->show();
    addTaskOpen = true;

    // Make necessary connections
    connect(atd, &AddTaskDisplay::closed, [this] () { addTaskOpen = false; });
    // Connect the buildtask symbol to the addtask slot of the mainwindow
    connect(atd, SIGNAL(sendTask(QString, URLAndMethod, QString, QString, QString, QString, QDateTime, QString, QString, int, int)),
            this, SLOT(buildTask(QString, URLAndMethod, QString, QString, QString, QString, QDateTime, QString, QString, int, int)));
}

// Opens the add VID task window
void BotWindow::openNewVIDTask() {
    if (addVIDTaskOpen) {
        // Show the currently open task window
        avidtd->raise();
        avidtd->setFocus();
        return;
    }

    // If there is a normal new task open, just close it
    if (addTaskOpen) { atd->close(); }

    // Build the window if it does not exist, otherwise just show it
    avidtd = new AddVIDTaskDisplay();
    avidtd->show();
    addVIDTaskOpen = true;

    // Make necessary connections
    connect(avidtd, &AddVIDTaskDisplay::closed, [this] () { addVIDTaskOpen = false; });
    // Connect the buildtask symbol to the addtask slot of the mainwindow
    connect(avidtd, SIGNAL(sendTask(QString, URLAndMethod, QString, QString, QString, QDateTime, QString, QString, QString, int, int)),
            this, SLOT(buildVIDTask(QString, URLAndMethod, QString, QString, QString, QDateTime, QString, QString, QString, int, int)));
}

// Opens the parser window
void BotWindow::openParser() {
    if (parserOpen) {
        // Show the currently open parser window
        parserDisp->raise();
        parserDisp->setFocus();
        return;
    }

    // Build the window if it does not exist
    parserDisp = new ProductParserDisplay();
    parserDisp->show();
    parserOpen = true;

    // Make necessary connections
    connect(parserDisp, &ProductParserDisplay::closed, [this] () { parserOpen = false; });
}

// Opens the profiles window
void BotWindow::openProfiles() {
    if (profilesOpen) {
        // Show the currently open profiles window
        profilesDisp->raise();
        profilesDisp->setFocus();
        return;
    }
    // Build the window if it does not exist
    profilesDisp = new ProfilesDisplay();
    profilesDisp->show();
    profilesOpen = true;

    // Make necessary connections
    connect(profilesDisp, &ProfilesDisplay::closed, [this] () { profilesOpen = false; });
}

// Opens the proxies window
void BotWindow::openProxies() {
    if (proxiesOpen) {
        // Show the currently open proxies window
        proxiesDisp->raise();
        proxiesDisp->setFocus();
        return;
    }
    // Build the window if it does not exist
    proxiesDisp = new ProxyDisplay();
    proxiesDisp->show();
    proxiesOpen = true;

    // Make necessary connections
    connect(proxiesDisp, &ProxyDisplay::closed, [this] () { proxiesOpen = false; });
}

// Opens the settings window
void BotWindow::openSettings() {
    if (settingsOpen) {
        // Show the currently open proxies window
        settingsDisp->raise();
        settingsDisp->setFocus();
        return;
    }
    // Build the window if it does not exist
    settingsDisp = new SettingsDisplay();
    settingsDisp->show();
    settingsOpen = true;

    // Make necessary connections
    connect(settingsDisp, &SettingsDisplay::closed, [this] () { settingsOpen = false; });
}