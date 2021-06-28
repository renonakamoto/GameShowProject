/****************************************
           入力パラメータ
****************************************/

// PixelShaderに送られてくるデータ構造
struct PS_IN
{
    float4 pos : SV_POSITION;
    float2 texture_pos : TEXCOORD0;
};

// テクスチャ情報
Texture2D SceneTexture : register(t0);
SamplerState Sampler   : register(s0);

Texture2D BlurMap : register(t1);


/****************************************
            エントリー関数
****************************************/
// エントリーポイント
float4 ps_main(PS_IN input) : SV_TARGET
{    
    // スクリーンの横幅
    float SCREEN_WIDTH  = 1280.0;
    // スクリーンの縦幅
    float SCREEN_HEIGHT = 720.0;
    // ずらすピクセル数
    float OFFSET_PIXEL  = 1.5;
    
    // ピクセルのオフセット値を計算
    float offset_u = OFFSET_PIXEL / SCREEN_WIDTH;
    float offset_v = OFFSET_PIXEL / SCREEN_HEIGHT;
    
    // ずらさない基準となるテクセルをサンプル
    float4 base_color = SceneTexture.Sample(Sampler, input.texture_pos);
    float4 color      = base_color;
    
    // 右にオフセット値分ずらしたテクセルをサンプル
    color += SceneTexture.Sample(Sampler, input.texture_pos + float2( offset_u,       0.0));
    // 左にオフセット値分ずらしたテクセルをサンプル                                 
    color += SceneTexture.Sample(Sampler, input.texture_pos + float2(-offset_u,       0.0));
    // 下にオフセット値分ずらしたテクセルをサンプル
    color += SceneTexture.Sample(Sampler, input.texture_pos + float2(      0.0,  offset_v));
    // 上にオフセット値分ずらしたテクセルをサンプル                      
    color += SceneTexture.Sample(Sampler, input.texture_pos + float2(      0.0, -offset_v));
    // 右下にオフセット値分ずらしたテクセルをサンプル
    color += SceneTexture.Sample(Sampler, input.texture_pos + float2( offset_u,  offset_v));
    // 右上にオフセット値分ずらしたテクセルをサンプル                     
    color += SceneTexture.Sample(Sampler, input.texture_pos + float2( offset_u, -offset_v));
    // 左下にオフセット値分ずらしたテクセルをサンプル
    color += SceneTexture.Sample(Sampler, input.texture_pos + float2(-offset_u,  offset_v));
    // 左上にオフセット値分ずらしたテクセルをサンプル
    color += SceneTexture.Sample(Sampler, input.texture_pos + float2(-offset_u, -offset_v));
    
    // サンプルした色の平均のを計算
    color /= 9.0;
    
    // BlurMapからテクセルをサンプリングし[r]成分を保存
    float t = BlurMap.Sample(Sampler, input.texture_pos).r;
    /*
        ベースのピクセルカラーとブラーのピクセルカラーを
        BlurMapから取得した値を使い補間する
    */
    color = lerp(base_color, color, t);
    
    // 出力
    return color;
}