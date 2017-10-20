#include "detector.h"

//排序函数的define
#define CV_IMPLEMENT_QSORT_EX( func_name, T, LT, user_data_type )                   \
void func_name( T *array, size_t total, user_data_type aux )                        \
{                                                                                   \
    int isort_thresh = 7;                                                           \
    T t;                                                                            \
    int sp = 0;                                                                     \
                                                                                    \
    struct                                                                          \
    {                                                                               \
        T *lb;                                                                      \
        T *ub;                                                                      \
    }                                                                               \
    stack[48];                                                                      \
                                                                                    \
    aux = aux;                                                                      \
                                                                                    \
    if( total <= 1 )                                                                \
        return;                                                                     \
                                                                                    \
    stack[0].lb = array;                                                            \
    stack[0].ub = array + (total - 1);                                              \
                                                                                    \
    while( sp >= 0 )                                                                \
    {                                                                               \
        T* left = stack[sp].lb;                                                     \
        T* right = stack[sp--].ub;                                                  \
                                                                                    \
        for(;;)                                                                     \
        {                                                                           \
            int i, n = (int)(right - left) + 1, m;                                  \
            T* ptr;                                                                 \
            T* ptr2;                                                                \
                                                                                    \
            if( n <= isort_thresh )                                                 \
            {                                                                       \
            insert_sort:                                                            \
                for( ptr = left + 1; ptr <= right; ptr++ )                          \
                {                                                                   \
                    for( ptr2 = ptr; ptr2 > left && LT(ptr2[0],ptr2[-1]); ptr2--)   \
                        CV_SWAP( ptr2[0], ptr2[-1], t );                            \
                }                                                                   \
                break;                                                              \
            }                                                                       \
            else                                                                    \
            {                                                                       \
                T* left0;                                                           \
                T* left1;                                                           \
                T* right0;                                                          \
                T* right1;                                                          \
                T* pivot;                                                           \
                T* a;                                                               \
                T* b;                                                               \
                T* c;                                                               \
                int swap_cnt = 0;                                                   \
                                                                                    \
                left0 = left;                                                       \
                right0 = right;                                                     \
                pivot = left + (n/2);                                               \
                                                                                    \
                if( n > 40 )                                                        \
                {                                                                   \
                    int d = n / 8;                                                  \
                    a = left, b = left + d, c = left + 2*d;                         \
                    left = LT(*a, *b) ? (LT(*b, *c) ? b : (LT(*a, *c) ? c : a))     \
                                      : (LT(*c, *b) ? b : (LT(*a, *c) ? a : c));    \
                                                                                    \
                    a = pivot - d, b = pivot, c = pivot + d;                        \
                    pivot = LT(*a, *b) ? (LT(*b, *c) ? b : (LT(*a, *c) ? c : a))    \
                                      : (LT(*c, *b) ? b : (LT(*a, *c) ? a : c));    \
                                                                                    \
                    a = right - 2*d, b = right - d, c = right;                      \
                    right = LT(*a, *b) ? (LT(*b, *c) ? b : (LT(*a, *c) ? c : a))    \
                                      : (LT(*c, *b) ? b : (LT(*a, *c) ? a : c));    \
                }                                                                   \
                                                                                    \
                a = left, b = pivot, c = right;                                     \
                pivot = LT(*a, *b) ? (LT(*b, *c) ? b : (LT(*a, *c) ? c : a))        \
                                   : (LT(*c, *b) ? b : (LT(*a, *c) ? a : c));       \
                if( pivot != left0 )                                                \
                {                                                                   \
                    CV_SWAP( *pivot, *left0, t );                                   \
                    pivot = left0;                                                  \
                }                                                                   \
                left = left1 = left0 + 1;                                           \
                right = right1 = right0;                                            \
                                                                                    \
                for(;;)                                                             \
                {                                                                   \
                    while( left <= right && !LT(*pivot, *left) )                    \
                    {                                                               \
                        if( !LT(*left, *pivot) )                                    \
                        {                                                           \
                            if( left > left1 )                                      \
                                CV_SWAP( *left1, *left, t );                        \
                            swap_cnt = 1;                                           \
                            left1++;                                                \
                        }                                                           \
                        left++;                                                     \
                    }                                                               \
                                                                                    \
                    while( left <= right && !LT(*right, *pivot) )                   \
                    {                                                               \
                        if( !LT(*pivot, *right) )                                   \
                        {                                                           \
                            if( right < right1 )                                    \
                                CV_SWAP( *right1, *right, t );                      \
                            swap_cnt = 1;                                           \
                            right1--;                                               \
                        }                                                           \
                        right--;                                                    \
                    }                                                               \
                                                                                    \
                    if( left > right )                                              \
                        break;                                                      \
                    CV_SWAP( *left, *right, t );                                    \
                    swap_cnt = 1;                                                   \
                    left++;                                                         \
                    right--;                                                        \
                }                                                                   \
                                                                                    \
                if( swap_cnt == 0 )                                                 \
                {                                                                   \
                    left = left0, right = right0;                                   \
                    goto insert_sort;                                               \
                }                                                                   \
                                                                                    \
                n = MIN( (int)(left1 - left0), (int)(left - left1) );               \
                for( i = 0; i < n; i++ )                                            \
                    CV_SWAP( left0[i], left[i-n], t );                              \
                                                                                    \
                n = MIN( (int)(right0 - right1), (int)(right1 - right) );           \
                for( i = 0; i < n; i++ )                                            \
                    CV_SWAP( left[i], right0[i-n+1], t );                           \
                n = (int)(left - left1);                                            \
                m = (int)(right1 - right);                                          \
                if( n > 1 )                                                         \
                {                                                                   \
                    if( m > 1 )                                                     \
                    {                                                               \
                        if( n > m )                                                 \
                        {                                                           \
                            stack[++sp].lb = left0;                                 \
                            stack[sp].ub = left0 + n - 1;                           \
                            left = right0 - m + 1, right = right0;                  \
                        }                                                           \
                        else                                                        \
                        {                                                           \
                            stack[++sp].lb = right0 - m + 1;                        \
                            stack[sp].ub = right0;                                  \
                            left = left0, right = left0 + n - 1;                    \
                        }                                                           \
                    }                                                               \
                    else                                                            \
                        left = left0, right = left0 + n - 1;                        \
                }                                                                   \
                else if( m > 1 )                                                    \
                    left = right0 - m + 1, right = right0;                          \
                else                                                                \
                    break;                                                          \
            }                                                                       \
        }                                                                           \
    }                                                                               \
}

//降序排序
#define hough_cmp_gt(l1,l2) (aux[l1] > aux[l2])
//排序函数的名称
CV_IMPLEMENT_QSORT_EX(Worker::icvHoughSortDescent32s, int, hough_cmp_gt, const int* )
CV_IMPLEMENT_QSORT_EX(Worker::icvHoughSortDescent32f, int, hough_cmp_gt, const float* )






//-------------------------------------------------------------------------------
//检测器，构造函数
Detector::Detector(ParamtersForDetector &param, QObject *parent)
    : QObject(parent)
{
    this->param = param;
    this->filter.SetParam(param.pos_filter_maxCount, param.pos_filter_maxDistance);
    //thread_pool = new QThreadPool(this);
    //thread_pool->setMaxThreadCount(QThread::idealThreadCount()-1);
    //thread_pool->setExpiryTimeout(3000);

}

//设定参数
void Detector::setParam(ParamtersForDetector &param)
{
    this->param = param;
    this->filter.SetParam(param.pos_filter_maxCount, param.pos_filter_maxDistance);
}

//检测器，析构函数
Detector::~Detector()
{
    //thread_pool->deleteLater();
}

//检测器，接收图像槽函数
void Detector::receiveFrame(FrameRawDataStruct frame)
{
    //新建worker对象
    Worker* worker = new Worker(param,frame);
    worker->setAutoDelete(true);

    //连接信号和槽
    qRegisterMetaType<DetectResultStruct>("DetectResultStruct");
    connect(worker, &Worker::resultReady, this, &Detector::receiveResult);

    //dowork,如果没有分配成功要删除对象
    if(!QThreadPool::globalInstance()->tryStart(worker))
    //if(!thread_pool->tryStart(worker))
        worker->deleteLater();
}

//接收多线程发送来的结果信号
void Detector::receiveResult(DetectResultStruct result)
{
    //结果坐标滤波
    if(param.pos_filter_en)
    {
        //检测到圆心
        if(result.satisfiedCycles.size() != 0)
        {
            cycleInfo &cycle = result.satisfiedCycles[result.theBestCycleIndex];

            if(filter.UpdateMeasure(cycle.centerPoint.x(),cycle.centerPoint.y(),cycle.radius))
            {
                filter.GetPrediction(cycle.centerPoint.rx(),cycle.centerPoint.ry(),cycle.radius);
                //防止越界
                if(cycle.centerPoint.x() > result.rawFrame.imgWidth)  cycle.centerPoint.setX(result.rawFrame.imgWidth);
                if(cycle.centerPoint.y() > result.rawFrame.imgHeigh)  cycle.centerPoint.setY(result.rawFrame.imgHeigh);
            }
            else
            {
                result.satisfiedCycles.clear();
                result.theBestCycleIndex = -1;
            }

        }
        //未检测到圆心
        else
        {
            if(filter.UpdateMeasure())
            {
                cycleInfo cycle;
                filter.GetPrediction(cycle.centerPoint.rx(),cycle.centerPoint.ry(),cycle.radius);
                cycle.accumCount = 0;//这里需要完善，暂时用0代替
                cycle.brightness = 0;//这里需要完善，暂时用0代替
                cycle.accumIntensity = 0;//这里需要完善，暂时用0代替
                result.satisfiedCycles.push_back(cycle);
                result.theBestCycleIndex = 0;

                //防止越界
                if(cycle.centerPoint.x() > result.rawFrame.imgWidth)  cycle.centerPoint.setX(result.rawFrame.imgWidth);
                if(cycle.centerPoint.y() > result.rawFrame.imgHeigh)  cycle.centerPoint.setY(result.rawFrame.imgHeigh);
            }
        }
    }

    //发射信号
    emit resultReady(result);
}


//--------------------------------------------------------------------------------------------
//检测器类的实现

//类构造函数
Worker::Worker(ParamtersForDetector param, FrameRawDataStruct frame, QObject *parent)
        : QObject(parent),
          param(param),
          frame(frame)
{
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t_start);

}

//析构函数
Worker::~Worker(void)
{

}

//重载run函数
void Worker::run()
{
    //1.构建result结构体
    getIntervalMillisecond();//计时开始
    DetectResultStruct result;
    result.rawFrame = frame;
    result.theBestCycleIndex = -1;
    result.elapsed_ms_accum = 0.0;
    result.elapsed_ms_blur = 0.0;
    result.elapsed_ms_canny = 0.0;
    result.elapsed_ms_checkPossibleCenter = 0.0;
    result.elapsed_ms_findPossibleCenter = 0.0;
    result.elapsed_ms_histogram = 0.0;
    result.elapsed_ms_scale = 0.0;
    result.elapsed_ms_sobel = 0.0;
    result.elapsed_ms_sortPossibleCenter = 0.0;
    result.elapsed_ms_total = 0.0;

    //2.构建图像、划出检测区域
    cv::Mat src_mat = cv::Mat(frame.imgHeigh, frame.imgWidth, CV_8UC1, (void*)frame.imgData.constData());
    cv::Mat roi_mat;
    if(param.pos_limit_en)
    {
        int x = (frame.imgWidth * param.pos_limit_left)/100;
        int y = (frame.imgHeigh * param.pos_limit_top)/100;
        int w = frame.imgWidth*(param.pos_limit_right - param.pos_limit_left)/100;
        int h = frame.imgHeigh*(param.pos_limit_bottom - param.pos_limit_top)/100;
        if(w < 1) w = 1;
        if(h < 1) h = 1;
        roi_mat = src_mat(cv::Rect(x, y, w, h));
    }
    else
    {
        roi_mat = src_mat;
    }

    //3.对图像进行降采样
    cv::Mat resample_mat;
    if((param.img_resample_size != QSize(0,0)) && (frame.imgWidth > param.img_resample_size.width()))
    {
        //如果原图尺寸大于降采样图的尺寸，缩小
        int width = (roi_mat.cols * param.img_resample_size.width()) / frame.imgWidth;
        int height = (roi_mat.rows * param.img_resample_size.height()) / frame.imgHeigh;
        result.imgROI = QImage(width, height, QImage::Format_Grayscale8);
        resample_mat = cv::Mat(height, width, CV_8UC1, (void*)result.imgROI.bits(), result.imgROI.bytesPerLine());
        cv::resize(roi_mat, resample_mat, resample_mat.size());
    }
    else//否则尺寸不变；
    {
        //拷贝过来
        resample_mat = roi_mat;
        result.imgROI = QImage(roi_mat.data, roi_mat.cols, roi_mat.rows, roi_mat.step, QImage::Format_Grayscale8);//.copy(0,0,roi_mat.cols, roi_mat.rows);
    }

    result.elapsed_ms_scale = getIntervalMillisecond();

    //4.对图像进行滤波
    //cv::Mat src = cv::Mat(result.imgROI.height(), result.imgROI.width(), CV_8UC1, (void*)result.imgROI.constBits(), result.imgROI.bytesPerLine());
    result.imgBlured = QImage(result.imgROI.size(),QImage::Format_Grayscale8);
    cv::Mat blur = cv::Mat(result.imgBlured.height(), result.imgBlured.width(), CV_8UC1, (void*)result.imgBlured.constBits(), result.imgBlured.bytesPerLine());
    int ksize;
    if(param.img_filt_level < 3) ksize = 3;
    else    ksize = param.img_filt_level;
    switch(param.img_filt_type)
    {
    case ParamtersForDetector::FILT_BLUR:{//均值滤波
            cv::blur(resample_mat, blur, cv::Size(ksize,ksize));
            break;}
    case ParamtersForDetector::FILT_GAUSSIAN_BLUR:{//高斯滤波
            if(ksize%2 == 0) ksize++;
            cv::GaussianBlur(resample_mat, blur, cv::Size(ksize,ksize),0);
            break;}
    case ParamtersForDetector::FILT_MEDIAN:{//中值滤波
            if(ksize%2 == 0) ksize++;
            cv::medianBlur(resample_mat, blur, ksize);
            break;}
    case ParamtersForDetector::FILT_BILATERAL:{//双边滤波
            cv::bilateralFilter(resample_mat, blur, param.img_filt_level, param.img_filt_level*2, param.img_filt_level/2);
            break;}
    default://无滤波
            result.imgBlured = result.imgROI;
            blur = resample_mat;
    }
    result.elapsed_ms_blur = getIntervalMillisecond();

    //5.计算直方图
    cv::MatND histogram = getHistogram(blur);
    result.imgHistogram = Histogram2QImage(histogram);
    result.elapsed_ms_histogram = getIntervalMillisecond();

    //6.开始检测
    findCircles(blur,result);

    //7.其他附加信息
    result.count_used_thread = QThreadPool::globalInstance()->activeThreadCount();
    result.resampleSize = (param.img_resample_size != QSize(0,0)) ? param.img_resample_size : QSize(frame.imgWidth, frame.imgHeigh);

    if(param.pos_limit_en)
    {
        result.pos_limit_en = true;
        result.ROIRect = QRect(QPoint(param.pos_limit_left,param.pos_limit_top),
                               QPoint(param.pos_limit_right,param.pos_limit_bottom));
    }
    else
    {
        result.pos_limit_en = false;
        result.ROIRect = QRect(0,0,0,0);

    }

    coordinateConversion(QPointF(param.expected_pos_x * result.imgROI.width() / 100, param.expected_pos_y * result.imgROI.height() / 100), result.expectCenterPoint);
    result.radius_max = param.radius_max;

    //7.2结果坐标换算
    for(uint i=0; i<result.satisfiedCycles.size(); i++)
    {
        cycleInfo &cycle = result.satisfiedCycles[i];
        QPointF newCenterPoint;
        coordinateConversion(cycle.centerPoint, newCenterPoint);
        cycle.centerPoint = newCenterPoint;
    }

    //8.发射信号
    emit resultReady(result);

}



//查找罐口函数
void Worker::findCircles(cv::Mat &img, DetectResultStruct &result)
{
    //-----------------------------------------------------------------------------------------
    //第一步，根据图像边缘的梯度画圆的法线，结果存在accum里

    //1.1.求图像的轮廓
    result.imgEdges = QImage(result.imgBlured.size(),QImage::Format_Grayscale8);
    cv::Mat edges(result.imgEdges.height(), result.imgEdges.width(), CV_8UC1, result.imgEdges.bits(), result.imgEdges.bytesPerLine());
    cv::Canny(img, edges, param.canny_threshold1, param.canny_threshold2);
    result.elapsed_ms_canny = getIntervalMillisecond();//计时

    //1.2.计算原图的梯度,结果在dx,dy中
    cv::Mat dx(img.rows,img.cols,CV_16SC1);
    cv::Mat dy(img.rows,img.cols,CV_16SC1);
    cv::Sobel(img,dx,CV_16S,1,0,3);
    cv::Sobel(img,dy,CV_16S,0,1,3);
    result.elapsed_ms_sobel = getIntervalMillisecond();

    //1.3.hough梯度空间变换，变换后的结果存在accum中
    std::vector<cv::Point> nz(img.rows*img.cols);
    double dp = param.hough_dp;
    if(dp < 1.f) dp=1.f;
    float idp = 1.f/dp;
    cv::Mat accum = cv::Mat(cvCeil((float)img.rows*idp)+2, cvCeil((float)img.cols*idp)+2, CV_32SC1, cv::Scalar(0));
    int rows = img.rows;
    int cols = img.cols;
    int* adata=(int*)(accum.data);
    int arows = accum.rows-2;
    int acols = accum.cols-2;
    int astep = accum.step/sizeof(adata[0]);
    const int SHIFT = 10, ONE = 1<< SHIFT;
    int min_radius=param.radius_min;
    int max_radius=param.radius_max;
    nz.clear();

    for(int y=0; y<rows; y++)
    {
        const uchar* edges_row = edges.ptr<uchar>(y);
        const short* dx_row = dx.ptr<short>(y);
        const short* dy_row = dy.ptr<short>(y);
        for(int x=0; x<cols; x++)
        {
            float vx = dx_row[x];
            float vy = dy_row[x];

            if(!edges_row[x] || (vx==0 && vy==0))
                continue;

            float mag = sqrt(vx*vx+vy*vy);
            if(mag < 1) continue;
            int sx = cvRound((vx*idp)*ONE/mag);
            int sy = cvRound((vy*idp)*ONE/mag);
            int x0 = cvRound((x*idp)*ONE);
            int y0 = cvRound((y*idp)*ONE);
            int x1,y1,x2,y2;
            //从最小圆半径到最大圆半径对每个梯度方向进行转换
            for(int k1=0; k1<2; k1++)
            {
                x1 = x0 + min_radius * sx;
                y1 = y0 + min_radius * sy;
                for(int r=min_radius; r<=max_radius; x1 += sx, y1 += sy, r++)
                {
                    x2 = x1 >> SHIFT;
                    y2 = y1 >> SHIFT;
                    if((unsigned)x2 >= (unsigned)acols || (unsigned)y2 >= (unsigned)arows)
                        break;
                    adata[y2*astep+x2]++;//这里是画点+1；
                }
                sx = -sx;
                sy = -sy;
            }
            //记录计算过的非零点
            nz.push_back(cv::Point(x,y));
        }
    }
    result.count_nz = nz.size();
    result.elapsed_ms_accum = getIntervalMillisecond();
    //将32SC1图像转换成可以显示的图像
    double min,max;
    cv::minMaxLoc(accum,&min,&max);
    result.imgAccum = QImage(accum.cols, accum.rows, QImage::Format_Grayscale8);
    cv::Mat dstImg = cv::Mat(accum.rows, accum.cols, CV_8UC1, result.imgAccum.bits(), result.imgAccum.bytesPerLine());
    accum.convertTo(dstImg,CV_8UC1,-255/max,255);

    if(nz.empty())
    {
        result.elapsed_ms_total = getLivedMillisecond();
        return;//出错返回
    }


    //-----------------------------------------------------------------------------------------
    //第二步，查找可能的圆心点，并按该点在accum里的亮度排序

    //2.1.遍历accum，查找可能的圆心,结果存在centers里面,注意类型不同
    std::vector<int> centers(nz.size());
    int acc_threshold = param.acc_threshold;
    adata = (int*)accum.data;
    centers.clear();
    arows = accum.rows-2;
    acols = accum.cols-2;
    for(int y=1; y<arows-1; y++)
    {
        for(int x=1; x<acols-1; x++)
        {
            int base = y*(acols+2)+x;

            if((adata[base] > acc_threshold) && \
                    (adata[base] > adata[base-1]) && (adata[base] > adata[base+1]) && \
                    (adata[base] > adata[base-acols-2]) && (adata[base] > adata[base+acols+2]))
            {
                    centers.push_back(base);
            }
        }
    }
    result.count_possible_center = centers.size();
    result.elapsed_ms_findPossibleCenter = getIntervalMillisecond();
    if(centers.empty())
    {
        result.elapsed_ms_total = getLivedMillisecond();
        return;//出错返回
    }


    //2.2.对所有圆心点的坐标按照在accum中的亮度值降序排序
    icvHoughSortDescent32s((int*)centers.data(),centers.size(),adata);
    result.elapsed_ms_sortPossibleCenter = getIntervalMillisecond();

    //-----------------------------------------------------------------------------------------
    //第三步，在可能是圆心点centers中进一步筛选符合条件的圆

    //3.1.遍历每一个centers中的点
    float min_dist2=(float)param.min_dist*(float)param.min_dist;
    float min_radius_f = (float)param.radius_min;
    float max_radius_f = (float)param.radius_max;
    qreal time_limit = param.detector_timelimit_ms;
    acols = accum.cols-2;

    for(unsigned int i=0,j; i < centers.size(); i++)
    {
        //3.1.0.防止计算超时
        if(getLivedMillisecond() > time_limit)
            break;

        //3.1.1.取第一个圆心，将圆心的坐标换算到原图中的坐标cx0,cy0
        int ofs = centers[i];
        int y = ofs / (acols+2);
        int x = ofs - (y*(acols+2));
        float cx0 = (float)((x+0.5f)*dp);
        float cy0 = (float)((y+0.5f)*dp);

        //3.1.2.如果中心点和之前计算过的中心点相邻，则排除
        cycleInfo current;
        float dx,dy;
        for(j = 0; j < result.satisfiedCycles.size(); j++)
        {
            current = result.satisfiedCycles[j];
            dx = current.centerPoint.x()-cx0;
            dy = current.centerPoint.y()-cy0;
            if((dx*dx+dy*dy) < min_dist2)
                break;
        }
        if(j < result.satisfiedCycles.size())
            continue;

        //3.1.3.计算当前中心点(cx0,cy0)到图像中每一个点的距离,存在dist_buf0中
        uint nz_count = nz.size();
        cv::Mat dist_circles(1,nz_count,CV_32FC1);

        std::vector<int>   sort_circles(nz_count);
        sort_circles.resize(nz_count);
        int* sorts_circles = sort_circles.data();
        int circles_count=0;

        float* ddata_circles= (float*)dist_circles.data;

        //遍历edges图像中的所有非零点nz
        cv::Point *point = nz.data();
        for(j = 0; j<nz_count; j++)
        {
            float _dx0,_dy0,_dist0;
            _dx0 = cx0 - point->x;
            _dy0 = cy0 - point->y;

            _dist0 = std::powf((_dx0*_dx0 + _dy0*_dy0),0.5f);

            if(min_radius_f<=_dist0 && _dist0<=max_radius_f)
            {//对圆的半径进行记录
                ddata_circles[circles_count] = _dist0;
                sorts_circles[circles_count] = circles_count;
                circles_count++;
            }
            point++;
        }

        sort_circles.resize(circles_count);

        dist_circles.cols = circles_count;

        if(circles_count==0)
            continue;

        //对圆的半径进行排序
        //icvHoughSortDescent32f(sorts_circles,circles_count,ddata_circles);

        //3.1.4.估算最佳半径
        float dr=(float)dp;
        float r_best = 0;
        int max_count = 0;
        int start_idx,count;
        float start_dist;
        float* ddata;
        int* sdata;

        start_idx = circles_count-1;
        count = circles_count;
        ddata = ddata_circles;
        sdata = sorts_circles;

        start_dist = ddata[sdata[start_idx]];
        for(int j=count - 2; j>=0; j--)
        {
            float d=ddata[sdata[j]];

            if(d>max_radius_f)
                break;

            if(d-start_dist > dr)
            {
                float r_cur = ddata[sdata[(j + start_idx)/2]];
                if((start_idx-j)*r_best >= max_count*r_cur || (r_best < FLT_EPSILON && start_idx-j >= max_count))
                {
                    r_best=r_cur;
                    max_count=start_idx-j;
                }
                start_dist=d;
                start_idx=j;
            }
        }

        //3.1.5.按accum值筛选，并记录
        if(max_count > acc_threshold)
        {
            current.centerPoint.setX(cx0);//中心点x
            current.centerPoint.setY(cy0);//中心点y
            current.radius = r_best;//半径
            current.accumCount = max_count;//密度
            current.accumIntensity = max_count/(6.28*r_best);//像素占圆周的比例
            //求圆心的中心亮度,先检测边界，然后求中心7*7范围的亮度
            if((cx0+7) >= img.cols) cx0 = img.cols-7;
            if((cy0+7) >= img.rows) cy0 = img.rows-7;
            current.brightness = cv::mean(cv::Mat(img, cv::Rect(cx0, cy0, 7, 7)))[0];
            result.satisfiedCycles.push_back(current);

            //选一个最优的园,符合亮度的入围，然后根据accum选一个最优的
            if(current.brightness < (param.brightness_max *255))
            {
                if(result.theBestCycleIndex >=0)
                {
                    cycleInfo cycle1 = result.satisfiedCycles[result.theBestCycleIndex];
                   if(cycle1.accumCount < max_count)
                       result.theBestCycleIndex = result.satisfiedCycles.size()-1;
                }
                else
                   result.theBestCycleIndex =  result.satisfiedCycles.size()-1;
            }
        }
    }
    result.elapsed_ms_checkPossibleCenter = getIntervalMillisecond();
    result.elapsed_ms_total = getLivedMillisecond();

    return;
}

//坐标转换，从ROI转换到原图
bool Worker::coordinateConversion(QPointF &coord_roi, QPointF &coord_src)
{
    qreal x0 = coord_roi.x();
    qreal y0 = coord_roi.y();
    qreal x,y;
    if(param.pos_limit_en)
    {
        if(param.img_resample_size != QSize(0,0))
        {
            x = (x0 + (param.img_resample_size.width() * param.pos_limit_left / 100)) * frame.imgWidth / param.img_resample_size.width();
            y = (y0 + (param.img_resample_size.height() * param.pos_limit_top / 100)) * frame.imgHeigh / param.img_resample_size.height();
        }
        else
        {
            x = x0 + (param.pos_limit_left * frame.imgWidth / 100);
            y = y0 + (param.pos_limit_top * frame.imgHeigh / 100);
        }
    }
    else
    {
        if(param.img_resample_size != QSize(0,0))
        {
            x = x0 * frame.imgWidth / param.img_resample_size.width();
            y = y0 * frame.imgHeigh / param.img_resample_size.height();
        }
        else
        {
            x = x0;
            y = y0;
        }
    }
    coord_src.setX(x);
    coord_src.setY(y);
    return true;

}

//Mat转QImage(拷贝)
QImage Worker::MatCopy2QImage(const cv::Mat &mat)
{
    // 处理CV_8UC1类型的图像
    if(mat.type() == CV_8UC1)
    {
        QImage image(mat.cols, mat.rows, QImage::QImage::Format_Grayscale8);
        //QImage image(mat.cols, mat.rows, QImage::QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        //image.setColorCount(256);
        //for(int i = 0; i < 256; i++)
        //{
            //image.setColor(i, qRgb(i, i, i));
        //}
        // Copy input Mat
        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }
    // 处理CV_32SC1类型的图像
    else if(mat.type() == CV_32SC1)
    {
        //将32SC1图像转换成可以显示的图像
        double min,max;
        cv::minMaxLoc(mat,&min,&max);
        cv::Mat dstImg;
        mat.convertTo(dstImg,CV_8UC1,-255/max,255);

        QImage image(dstImg.cols, dstImg.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar *pSrc = dstImg.data;
        for(int row = 0; row < dstImg.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, dstImg.cols);
            pSrc += dstImg.step;
        }
        return image;
    }
    else
    {
        return QImage();
    }
}

//Mat转QImage(缩放)(QImage::Format_Indexed8)
QImage Worker::MatScaled2QImage(const cv::Mat &mat,double dp)
{
    // 只处理CV_8UC1类型的图像
    if(mat.type() == CV_8UC1)
    {
        cv::Mat dst;
        //对图像进行缩放
        cv::resize(mat,dst,cv::Size(0,0),1/dp,1/dp,cv::INTER_LINEAR);
        QImage image(dst.cols, dst.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar *pSrc = dst.data;
        for(int row = 0; row < dst.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, dst.cols);
            pSrc += dst.step;
        }
        return image;
    }
    else
    {
        return QImage();
    }
}

//计算直方图
cv::MatND Worker::getHistogram(const cv::Mat &image)
{
    cv::MatND hist;

    int histSize[1]={256};
    float hranges[2]={0.0,255.0};
    const float* ranges[1];
    int channels[1]={0};
    ranges[0]=hranges;
    // Compute histogram
    cv::calcHist(&image,
                1,			// histogram of 1 image only
                channels,	// the channel used
                cv::Mat(),	// no mask is used
                hist,		// the resulting histogram
                1,			// it is a 1D histogram
                histSize,	// number of bins
                ranges		// pixel value range
                );

    return hist;
}

//直方图转QImage(QImage::Format_ARGB32_Premultiplied)
QImage Worker::Histogram2QImage(const cv::Mat &hist)
{
    if(hist.empty())
    {
        return QImage();
    }
    else
    {
        //创建直方图图像，尺寸固定为256*128
        QImage image(256, 128, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgba(i,i,i,i));
        }

        double max_val;  //直方图的最大值
        cv::minMaxLoc(hist, 0, &max_val, 0, 0); //计算直方图最大值

        double alpha = 127.f/max_val;
        cv::Mat matCalc;
        hist.convertTo(matCalc,CV_8UC1,alpha,0);

        // 绘制图像
        uchar *pSrc,*pDest;
        for(int row = 0; row < 128; row++)//cols=1 rows=256
        {
            pSrc = matCalc.data;
            pDest = image.scanLine(row);
            for(int col = 0; col < 256; col ++)
            {
                if(128-row < pSrc[col])  {pDest[col] = 255;}
                else             {pDest[col] = 0;}
            }
        }
        return image.convertToFormat(QImage::Format_ARGB32_Premultiplied);
    }
}

//Otsu法计算二值化阈值
int Worker::thresholdOtsu(cv::Mat &img,cv::MatND &histogram)
{
    int height=img.rows;
    int width=img.cols;

    //normalize histogram
    long size = height * width;
    for(int i = 0; i < 256; i++)
    {
        histogram.at<float>(i) = histogram.at<float>(i) / size;
    }

    //average pixel value
    float avgValue=0;
    for(int i=0; i < 256; i++)
    {
        avgValue += i * histogram.at<float>(i);  //整幅图像的平均灰度
    }
    int threshold;
    float maxVariance=0;
    float w = 0, u = 0;
    for(int i = 0; i < 256; i++)
    {
        w += histogram.at<float>(i);  //假设当前灰度i为阈值, 0~i 灰度的像素(假设像素值在此范围的像素叫做前景像素) 所占整幅图像的比例
        u += i * histogram.at<float>(i);  // 灰度i 之前的像素(0~i)的平均灰度值： 前景像素的平均灰度值

        float t = avgValue * w - u;
        float variance = t * t / (w * (1 - w) );
        if(variance > maxVariance)
        {
            maxVariance = variance;
            threshold = i;
        }
    }
    if(threshold>255)
        threshold=255;
    return threshold;
}

//私有函数，计算耗时
qreal Worker::getIntervalMillisecond()
{
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t2);
    qreal retval;

    retval = (t2.QuadPart - t1.QuadPart)*1000.0/tc.QuadPart;
    t1 = t2;
    return retval;
}

//私有函数，计算类的生存时间
qreal Worker::getLivedMillisecond()
{
    QueryPerformanceCounter(&t_current);
    return(t_current.QuadPart - t_start.QuadPart)*1000.0/tc.QuadPart;
}






