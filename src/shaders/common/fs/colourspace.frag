#version 130

struct hsv_t{
    float h; float s; float v; float delta;
};

hsv_t shimmer_hsv(vec4 col){
    float cmin = min(min(col.r, col.g), col.b);
    float H = 0;
    float S = 0;
    float V = max(max(col.r, col.g), col.b);
    float delta = V - cmin;

    if(V != 0){
        S = delta / V;
    }

    if(delta != 0){
        if(V == col.r){
             H = mod((col.g - col.b) / delta, 6);
        }
        else if (V == col.g){
            H = (col.b-col.r) / delta + 2;
        }
        else if (V == col.b){
            H = (col.r - col.g) / delta + 4;
        }
    }
    H = H / 6.28319 * 360;
    return hsv_t(H, S, V, delta);
}
