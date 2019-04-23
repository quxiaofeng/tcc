double get_contrast(double mean, double std){
    double eps = 0.0001;
    return std / (mean + eps);
}