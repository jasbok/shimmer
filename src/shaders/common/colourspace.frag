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

vec4 shimmer_rgb(hsv_t hsv){
    float C = hsv.s * hsv.v;
    float H = hsv.h / 60;
    float X = C * (1 - abs(mod(H, 2) - 1));

    vec3 rgb = vec3(0, 0,0);
    if(0 <= H && H <= 1){
        rgb = vec3(C, X, 0);
    }
    else if (1 < H && H <= 2){
        rgb = vec3(X, C, 0);
    }
    else if(2 < H && H <= 3){
        rgb = vec3(0, C, X);
    }
    else if(3 < H && H <= 4){
        rgb = vec3(0, X, C);
    }
    else if(4 < H && H <= 5){
        rgb = vec3(X, 0, C);
    }
    else if(5 < H && H <= 6){
        rgb = vec3(C, 0, X);
    }
    float m = hsv.v - C;
    return vec4(rgb.r + m, rgb.g + m, rgb.b + m, 1.0);
}
