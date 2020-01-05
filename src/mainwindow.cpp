#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);

    // contact listener instance (for collision callbacks)
    contactListenerInstance = new ContactListener(itemList);


    // BGM
    BGM = new QMediaPlayer();
    BGM->setMedia(QUrl("qrc:/sounds/platformer_bgm.mp3"));
    BGM->play();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::showEvent(QShowEvent *) {

    // Setting QGraphicsScene
    scene = new QGraphicsScene(0, 0, width(), ui->graphicsView->height());
    scene->setBackgroundBrush(QBrush(QColor("black")));
    ui->graphicsView->setScene(scene);


    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    world->SetContactListener(contactListenerInstance);

    // Setting Size
    GameItem::setGlobalSize(QSizeF(32, 18), size());

    // Create ground
    int offset = 1;
    itemList.push_back(new Land(16, 1.5, 256, 3, QPixmap(":/ground.png").scaled(width()*(offset+8), height()/6.0), world, scene));

    // Create platforms
    itemList.push_back(new Platform(20, 4.5, 4, 2, QPixmap(":/sprites/industrial.v2.png"), world, scene));
    itemList.push_back(new Platform(24.5, 4.5, 4, 2, QPixmap(":/sprites/industrial.v2.png"), world, scene));
    itemList.push_back(new Platform(29, 4.5, 4, 2, QPixmap(":/sprites/industrial.v2.png"), world, scene));
    itemList.push_back(new Platform(33.5, 4.5, 4, 2, QPixmap(":/sprites/industrial.v2.png"), world, scene));

    itemList.push_back(new Platform(50, 10, 4, 2, QPixmap(":/sprites/industrial.v2.png"), world, scene));
    itemList.push_back(new Platform(52.5, 10, 4, 2, QPixmap(":/sprites/industrial.v2.png"), world, scene));
    itemList.push_back(new Platform(55, 10, 4, 2, QPixmap(":/sprites/industrial.v2.png"), world, scene));

    // Create platforms
    itemList.push_back(new Platform(70, 4.5, 4, 2, QPixmap(":/sprites/industrial.v2.png"), world, scene));
    itemList.push_back(new Platform(72.5, 4.5, 4, 2, QPixmap(":/sprites/industrial.v2.png"), world, scene));
    itemList.push_back(new Platform(75, 4.5, 4, 2, QPixmap(":/sprites/industrial.v2.png"), world, scene));
    itemList.push_back(new Platform(77.5, 4.5, 4, 2, QPixmap(":/sprites/industrial.v2.png"), world, scene));



    // Create main character
    ziggy = new Ziggy(10.0f, 5.0f, 1.0f, 0.3f, &timer, QPixmap(":/sprites/industrial.v2.png"), world, scene);
    itemList.push_back(ziggy);
    qApp->installEventFilter(ziggy);


    // Create slimes
    itemList.push_back(new Slime(30.0f, 20.0f, 1.0f, 0.3f, &timer, QPixmap(":/sprites/industrial.v2.png"), world, scene));
    itemList.push_back(new Slime(35.0f, 20.0f, 1.0f, 0.3f, &timer, QPixmap(":/sprites/industrial.v2.png"), world, scene));
    itemList.push_back(new Slime(42.0f, 20.0f, 1.0f, 0.3f, &timer, QPixmap(":/sprites/industrial.v2.png"), world, scene));
    itemList.push_back(new Slime(44.0f, 20.0f, 1.0f, 0.3f, &timer, QPixmap(":/sprites/industrial.v2.png"), world, scene));
    itemList.push_back(new Slime(50.0f, 20.0f, 1.0f, 0.3f, &timer, QPixmap(":/sprites/industrial.v2.png"), world, scene));
    itemList.push_back(new Slime(55.0f, 20.0f, 1.0f, 0.3f, &timer, QPixmap(":/sprites/industrial.v2.png"), world, scene));
    itemList.push_back(new Slime(60.0f, 20.0f, 1.0f, 0.3f, &timer, QPixmap(":/sprites/industrial.v2.png"), world, scene));
    itemList.push_back(new Slime(65.0f, 20.0f, 1.0f, 0.3f, &timer, QPixmap(":/sprites/industrial.v2.png"), world, scene));
    itemList.push_back(new Slime(70.0f, 20.0f, 1.0f, 0.3f, &timer, QPixmap(":/sprites/industrial.v2.png"), world, scene));
    itemList.push_back(new Slime(75.0f, 20.0f, 1.0f, 0.3f, &timer, QPixmap(":/sprites/industrial.v2.png"), world, scene));
    itemList.push_back(new Slime(80.0f, 20.0f, 1.0f, 0.3f, &timer, QPixmap(":/sprites/industrial.v2.png"), world, scene));
    itemList.push_back(new Slime(90.0f, 20.0f, 1.0f, 0.3f, &timer, QPixmap(":/sprites/industrial.v2.png"), world, scene));


    // create ResetBall
    // itemList.push_back(new ResetBall(10.0f, 15.0f, 0.5f, &timer, QPixmap(":/sprites/resetButton.png").scaled(height()/8.0,height()/8.0), world, scene));

    DebugDraw debugDraw(scene);
    world->SetDebugDraw(&debugDraw);
    debugDraw.SetFlags(b2Draw::e_shapeBit);


    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);
}

bool MainWindow::eventFilter(QObject *, QEvent *event) {
    if (event->type() == QEvent::MouseButtonPress) {
        QCoreApplication::quit();
    }

    if (event->type() == QEvent::MouseMove) {
    }

    if (event->type() == QEvent::MouseButtonRelease) {
    }


    return false;
}

void MainWindow::closeEvent(QCloseEvent *) {
    // Close event
    emit quitGame();
}

void MainWindow::tick() {
    world->Step(1.0f/60.0f, 6, 2);
    viewPortTranslate();
    gameItemRemoval();
    scene->update();
    ziggy->getHPBar()->update(ziggy->getHP());

    if (ziggy->getPosition().x > 110.0f && ziggy->getPosition().x < 112.0f) {
        spawnResetBall();
    }
}

void MainWindow::QUITSLOT() {
    std::cout << "Quit Game Signal received!" << std::endl ;

}


void MainWindow::viewPortTranslate() {
    QRectF scene_rect = scene->sceneRect();

    // qDebug() << "player: " << ziggy->getPosition().x << "\nleftBound: "<< scene->sceneRect().left() << "\nrightBound: " << scene->sceneRect().right();
    float playerScenePosX = ziggy->getPosition().x * (width() / 32.0);
    if (scene->sceneRect().right() - playerScenePosX < 450) {
        // std::cout << "too close to right" << std::endl;
        scene_rect.translate(5, 0);
        scene->setSceneRect(scene_rect);

    } else if (playerScenePosX - scene->sceneRect().left() < 450) {
        // std::cout << "too close to left" << std::endl;
        scene_rect.translate(-5, 0);
        scene->setSceneRect(scene_rect);

    }

}

void MainWindow::gameItemRemoval() {

    if (ContactListener::itemsScheduledForRemoval.empty()) {
        return;
    }


    std::vector<GameItem *>::iterator it = ContactListener::itemsScheduledForRemoval.begin();
    std::vector<GameItem *>::iterator end = ContactListener::itemsScheduledForRemoval.end();

    for (; it != end; ++it) {
        GameItem *itemToBeDeleted = *it;

        delete itemToBeDeleted;

        std::vector<GameItem *>::iterator it = std::find(ContactListener::itemsScheduledForRemoval.begin(),
                                                         ContactListener::itemsScheduledForRemoval.end(),
                                                         itemToBeDeleted);
              if (it != ContactListener::itemsScheduledForRemoval.end())
                  ContactListener::itemsScheduledForRemoval.erase(it);

        it = std::find(itemList.begin(), itemList.end(), itemToBeDeleted);
        if (it != itemList.end())
            itemList.erase(it);
    }

    ContactListener::itemsScheduledForRemoval.clear();
}

void MainWindow::spawnResetBall() {
    rsBall = new ResetBall(ziggy->getPosition().x, 30.0f, 0.5f, &timer, QPixmap(":/sprites/resetButton.png").scaled(height()/8.0,height()/8.0), world, scene);
    itemList.push_back(rsBall);
}



