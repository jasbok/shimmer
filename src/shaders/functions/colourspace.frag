vec4 get_hsv(vec4 col){
    float cmin = min(min(col.r, col.g), col.b);
    float V = max(max(col.r, col.g), col.b);
    float S = 0;
    float H = 0;
    float delta = V - cmin;

    if(V != 0){
        S = delta / V;
    }

    if(delta != 0){
        if(V == col.r){
            //H = 1.0472 * mod((col.g - col.b) / delta, 0.10472);
             H = mod((col.g - col.b) / delta, 6);
        }
        else if (V == col.g){
            //H = 1.0472 * (col.b-col.r) / delta + 0.0349066;
            H = (col.b-col.r) / delta + 2;
        }
        else if (V == col.b){
            //H = 1.0472 * (col.r - col.g) / delta + 0.0698132;
            H = (col.r - col.g) / delta + 4;
        }
    }
    H = H / 6.28319;
    return vec4(H, S, V, delta);
}
