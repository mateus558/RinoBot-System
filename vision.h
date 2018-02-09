#ifndef VISION_H
#define VISION_H

#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>
#include <QtConcurrent/QtConcurrent>
#include <QGraphicsScene>
// #include <Eigen/Dense>
#include <opencv2/opencv.hpp>
#include <queue>
#include <utility>
#include <vector>

#include "robot.h"
#include "utils.h"

using namespace std;
using namespace cv;

/*!
 * \brief The Vision class is used to extract useful information from an image for robot soccer using
 * computer vision algorithms.
 */

class Vision: public QThread {  Q_OBJECT
public:
    struct Perception{
        bool ball_found;
        pair<double, double> ball_vel;
        Point ball_pos, ball_last_pos;
        Point img_size;
        Point2d ball_pos_cm;
        std::vector<Robot> enemy_robots, team_robots;
        pVector map_area, atk_area, def_area;
        pVector ball_contour;
        pair<vector<int>, vector<int> > ball_color;
    };
private:
    bool stop, showArea, sentPoints, teamsChanged, showNames, showCenters, showErrors, trained, play = false;
    int mode, rows, cols, camid = 0, x_offset, y_offset, cont;
    double FPS, deltaT;

    Mat kmeans_centers, labels, centers;
    Perception info;
    QMutex mutex;
    QWaitCondition condition;
    QImage img;
    Mat raw_frame, transf_matrix;
    Mat vision_frame;
    VideoCapture cam;
    vector<int> low;
    Rect2d ball_tracker;
    vector<Rect2d> objects_tracker;
    vector<bool> track_init;
    vector<int> upper;
    pair<vector<int>, vector<int> > ball_color;
    Point ball_pos;
    bool ball_found;
    Point2d ball_pos_cm;
    Point ball_last_pos;
    Point x_axis_slope, def_centroid, atk_centroid;
    pVector map_points, tmap_points;
    pVector atk_points, tatk_points;
    pVector def_points, tdef_points;
    Matrix3d last_P;
    vector<Robot> robots;
    pair <double, double> LPF_Coefficients; // Coeficientes do LPF
    bool first_itr_LPF, LPF_flag; // Flag para a LPF

public slots:
    void updateFuzzyRobots(std::vector<Robot>);
    void updateMoverRobots(std::vector<Robot>);

signals:
    void infoPercepted(Vision::Perception);
    void processedImage(const QImage &image);
    void framesPerSecond(double FPS);
protected:
    void run();
    void msleep(int ms);
public:
    Vision(QObject *parent = 0);

    /************************************************************************************
     * PRÉ-PROCESSAMENTO DA IMAGEM                                                      *
     ************************************************************************************/

    /************************************************************************************
        @brief adjust_gamma Ajusta a luminosidade da imagem.

        @param gamma Valor de Gamma para o algoritmo.
        @param org Matriz com a imagem a ser aplicada o tratamento.
        @return a matriz com a luminosidade ajustada.
    ************************************************************************************/
    Mat adjust_gamma(double gamma, Mat org);

    /************************************************************************************
        @brief crop_image Corta uma determinada região da imagem. De acordo com o tamanho do campo

        @param org Image to use.
        @return Mat
     *************************************************************************************/
    Mat crop_image(Mat org);

    /************************************************************************************
        @brief proccess_frame Pré-processa a imagem.

        @return Mat
     *************************************************************************************/
    Mat proccess_frame(Mat, Mat);

    /************************************************************************************
     * DETECÇÃO E REPRESENTAÇÃO DOS ROBÔS                                               *
     ************************************************************************************/

    /************************************************************************************
        @brief draw_field Desenha os pontos-chave do campo. (Borda)

        @param frame Frame aonde os pontos-chave serão desenhados.
        @return Mat Frame com os pontos já desenhado.
     ************************************************************************************/
    Mat draw_field(Mat frame);

    /************************************************************************************
        @brief draw_robots Desenha os robôs e suas informações na tela.

        @param frame Frame where they will be draw.
        @param robots Robots to draw.
        @return Mat
    ************************************************************************************/
    Mat draw_robots(Mat frame, vector<Robot> robots);

    /************************************************************************************
        @brief detect_colors Returns a mask with the pixels in the given range (Thresholding).

        @param vision_frame Frame where the thresholding will be applied.
        @param low Lower limit of the pixel range.
        @param upper Upper limit of the pixel range.
        @return Mat
     ************************************************************************************/
    Mat detect_colors(Mat vision_frame, vector<int> low, vector<int> upper);

    /************************************************************************************
        @brief detect_objects Detecta o contorno dos objetos do jogo. Utilizando de um
                                    vetor com as informações de cor dos objetos.

        @param frame Frame utilizado para a detecção.
        @param robots Vetor dos robôs.
        @return Vetor de contorno dos objetos de jogo
     ************************************************************************************/
    pair<vector<vector<Vec4i> >, vector<pMatrix> > detect_objects(Mat frame, vector<Robot> robots);

    /************************************************************************************
        @brief fill_robots Identifica os robôs e computa suas centróides.

        @param contours Candidatos à robôs (contornos).
        @param robots Vetor de robôs com as informações que se tem até o momento.
        @return vector<Robot> O vetor de robôs com informações preenchidas.
     ************************************************************************************/
    vector<Robot> fill_robots(vector<pMatrix> contours, vector<Robot> robots);

    /************************************************************************************
     * FUNÇÕES DE CONFIGURAÇÃO                                                          *
     ************************************************************************************/

    /************************************************************************************
        @brief is_stopped Verifica se a thread continua executando.
     ************************************************************************************/
    bool isStopped() const;

    /************************************************************************************
        @brief is_open Verifica se o canal da câmera está aberto.
     ************************************************************************************/
    bool is_open();

    /************************************************************************************
        @brief open_camera Abre o recurso da câmera utilizando a identificação desta.

        @param camid Identificação da camera.
        @return Se a câmera foi aberta (ou não).
     ************************************************************************************/
    bool open_camera(int camid = CV_CAP_FIREWIRE);

    /************************************************************************************
        @brief Play Inicia a execução do Thread da visão.
     ************************************************************************************/
    void Play();

    /************************************************************************************
        @brief release_cam Libera o recurso da câmera.
     ************************************************************************************/
    void release_cam();

    /************************************************************************************
        @brief save_image Salva a imagem do frame atual.
     ************************************************************************************/
    void save_image();

    /************************************************************************************
        @brief setting_mode Processa o frame de acordo com o modo de configuração.

        @param raw_frame Frame "cru" capturado da câmera.
        @param vision_frame Frame processado da visão.
        @param low Limite inferior de Cor RGB.
        @param upper Limite superior de Cor RGB.
        @return Mat retorna o frame processado.
     ************************************************************************************/
    Mat setting_mode(Mat raw_frame, Mat vision_frame, vector<int> low, vector<int> upper);

    /************************************************************************************
        @brief show_area Informa se os pontos-chave do campo devem ser exibidos(ou não).

        @param show Flag iformando se deve exibir ou não os pontos-chave do campo.
     ************************************************************************************/
    void show_area(bool show);

    /************************************************************************************
        @brief show_centers Informa se as centróides dos obetos de jogo devem ser exibidos(ou não).

        @param show Flag iformando se deve exibir ou não os pontos-chave do campo.
     ************************************************************************************/
    void show_centers(bool show);

    /************************************************************************************
        @brief show_names Informa se os nomes dos objetos de jogo devem ser exibidos(ou não).

        @param show Flag iformando se deve exibir ou não os pontos-chave do campo.
     ************************************************************************************/
    void show_names(bool show);

    //TODO REMOVE
    void show_errors(bool show);

    /************************************************************************************
        @brief Stop Para a execução do Thread da visão.
     ************************************************************************************/
    void Stop();

    /************************************************************************************
        @brief switch_teams_areas Informa que as àreas dos times foram trocadas.
     ************************************************************************************/
    void switch_teams_areas();

    /************************************************************************************
        @brief switch_teams_areas Informa que as àreas dos times foram trocadas.
     ************************************************************************************/
    void togglePlay(bool play);

    /************************************************************************************
     * GETS & SETS                                                                      *
     ************************************************************************************/
    /*  atk_area                                                                     (s)*/
    void set_atk_area(pVector atk_points);

    /*  ball                                                                         (s)*/
    void set_ball(pair<vector<int>, vector<int> > ball);

    /*  camID                                                                      (g,s)*/
    int get_camID();
    void set_camid(int cam);

    /*  def_area                                                                     (s)*/
    void set_def_area(pVector def_points);

    /*  low                                                                          (g)*/
    vector<int> get_low();
    void set_low(vector<int> low);

    /*  mode                                                                         (s)*/
    void set_mode(int m = 0);

    /*  robots                                                                     (g,s)*/
    vector<Robot> get_robots();
    void set_robots(vector<Robot> robots);

    /*  upper                                                                        (s)*/
    void set_upper(vector<int> upper);
    vector<int> get_upper();

    // coeficiente do LPF
    void set_LPF_Coefficients(pair <double, double> coeff);

    pair <double, double> get_LPF_Coefficients();

    // flag do LPF
    void set_LPF_flag(bool lpfFlag);
    bool get_LPF_flag();

    ~Vision();
};

#endif // VISION_H

