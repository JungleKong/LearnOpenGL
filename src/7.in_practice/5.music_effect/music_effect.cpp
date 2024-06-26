#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <learnopengl/filesystem.h>
#include <learnopengl/shader_m.h>

#include <iostream>
#include <string.h>
#include <unistd.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;
const float radiuss[] = {
    0.04897801, 0.04850386, 0.04796331, 0.04737113, 0.04673566, 0.04605531, 0.04531953, 0.04451474, 0.04363234, 0.04267569,
    0.04155454, 0.04063207, 0.03961615, 0.03864587, 0.03773032, 0.03860237, 0.04921472, 0.06121136, 0.07323765, 0.08426154,
    0.09373472, 0.1013563,  0.1070172,  0.1107295,  0.1126557,  0.1132389,  0.1131309,  0.1129854,  0.1132936,  0.1143618,
    0.1162725,  0.1189098,  0.1219982,  0.125181,   0.1280827,  0.1303817,  0.1319725,  0.1328782,  0.1331561,  0.1328917,
    0.132165,   0.1310501,  0.1296589,  0.1281385,  0.1265532,  0.1249345,  0.1233696,  0.1219656,  0.1208398,  0.120133,
    0.1198476,  0.1197818,  0.1196535,  0.1191783,  0.1181742,  0.1166461,  0.1147448,  0.1126533,  0.1104798,  0.1082808,
    0.106055,   0.1037363,  0.1013244,  0.09882738, 0.09623145, 0.09361129, 0.09106209, 0.08863955, 0.08635261, 0.08415065,
    0.08191278, 0.07952181, 0.0769469,  0.0742567,  0.07153033, 0.06883884, 0.0662471,  0.06375294, 0.06135269, 0.0590428,
    0.05682987, 0.05468332, 0.05263272, 0.05066791, 0.04878673, 0.046983,   0.04722759, 0.04771164, 0.04811118, 0.04844096,
    0.04871317, 0.04893784, 0.04912329, 0.04927636, 0.0494027,  0.04950699, 0.04959307, 0.04961187, 0.04952716, 0.04933483,
    0.04904868, 0.04868515, 0.04825992, 0.04778799, 0.04728336, 0.046758,   0.04622025, 0.04567406, 0.04511689, 0.04453801,
    0.04392632, 0.04329307, 0.04269385, 0.04222717, 0.0420032,  0.04209515, 0.04250973, 0.04319537, 0.04407526, 0.045074,
    0.04593406, 0.04664395, 0.04722991, 0.04771355, 0.04811276, 0.04844226, 0.04871424, 0.05190587, 0.05592973, 0.06778088,
    0.07885582, 0.08830714, 0.09582846, 0.1015022,  0.1056636,  0.1085087,  0.1103052,  0.111451,   0.1124651,  0.1137352,
    0.1162725,  0.1189098,  0.1219982,  0.125181,   0.1280827,  0.1303817,  0.1319725,  0.1328782,  0.1331561,  0.1328917,
    0.132165,   0.1310501,  0.1296589,  0.1281385,  0.1265532,  0.1249345,  0.1233696,  0.1219656,  0.1208398,  0.120133,
    0.1198476,  0.1197818,  0.1196535,  0.1191783,  0.1181742,  0.1166461,  0.1147448,  0.1126533,  0.1104798,  0.1082808,
    0.106055,   0.1037363,  0.1013244,  0.09882738, 0.09623145, 0.09361129, 0.09106209, 0.08863955, 0.08635261, 0.08415065,
    0.08191278, 0.07952181, 0.0769469,  0.0742567,  0.07153033, 0.06883884, 0.0662471,  0.06375294, 0.06135269, 0.0590428,
    0.05682987, 0.05468332, 0.05263272, 0.05066791, 0.04878673, 0.046983,   0.04722759, 0.04771164, 0.04811118, 0.04844096,
};

const float translateX[] = {
-0.007759332,   
-0.007283092,
-0.006819377,
-0.006369091,
-0.005932792,
-0.005511706,
-0.005101252,
-0.004694013,
-0.004289965,
-0.003889309,
-0.003492309,
-0.00309917,
-0.002710112,
-0.002325454,
-0.001945321,
-0.001570096,
-0.001199853,
-0.000834865,
-0.000475343,
-0.000121444,
0.000226458,
0.000568351,
0.000568351,
0.000903925,
0.001233003,
0.001555444,
0.001871038,
0.002179587,
0.002480885,
0.0027748,
0.003061212,
0.003339856,
0.003610746,
0.003873443,
0.004128116,
0.004374467,
0.004612304,
0.004841633,
0.005062303,
0.005274127,
0.005477058,
0.005670975,
0.005855763,
0.006031384,
0.006197697,
0.006354577,
0.006502008,
0.006639964,
0.006768295,
0.006887085,
0.006996075,
0.007095362,
0.00718492,
0.007264708,
0.007334604,
0.007394693,
0.007444955,
0.007485324,
0.007515838,
0.007536505,
0.007547345,
0.007548424,
0.007539685,
0.007521191,
0.007492972,
0.007455118,
0.007407619,
0.007350602,
0.007284109,
0.007208134,
0.007122839,
0.007028311,
0.006924564,
0.006811767,
0.006689998,
0.00655935,
0.006419919,
0.00627184,
0.006115285,
0.005950286,
0.005777074,
0.005595646,
0.005406344,
0.005209156,
0.005004272,
0.004791883,
0.004572176,
0.004345228,
0.004105696,
0.003826372,
0.003512085,
0.003165954,
0.002788516,
0.002380079,
0.001940876,
0.001471527,
0.000972356,
0.000443903,
-0.000113451,
-0.000699191,
-0.001312734,
-0.001953794,
-0.002621657,
-0.0033157,
-0.004035598,
-0.004780522,
-0.005550075,
-0.006343408,
-0.007160222,
-0.0079996,
-0.008860963,
-0.00974363,
-0.01064697,
-0.01157029,
-0.01251291,
-0.01347405,
-0.01445301,
-0.01544901,
-0.01646124,
-0.01748929,
-0.01853196,
-0.01958875,
-0.02065918,
-0.02174908,
-0.02285621,
-0.02397803,
-0.02511415,
-0.02626381,
-0.02742652,
-0.02860161,
-0.02978184,
-0.03094616,
-0.03209241,
-0.03322068,
-0.03433031,
-0.03542103,
-0.03649276,
-0.03754498,
-0.03857753,
-0.03959005,
-0.04058249,
-0.04155441,
-0.04250556,
-0.04343578,
-0.04434473,
-0.04523245,
-0.04609872,
-0.046943,
-0.04776555,
-0.04856574,
-0.04934368,
-0.0500993,
-0.05083224,
-0.05154248,
-0.05222987,
-0.05289435,
-0.05353566,
-0.05415386,
-0.05474892,
-0.05532053,
-0.05586891,
-0.05639373,
-0.05689498,
-0.05737288,
-0.05782701,
-0.05825776,
-0.05866491,
-0.05904843,
-0.05940843,
-0.05974487,
-0.0600577,
-0.06034708,
-0.06061313,
-0.06085575,
-0.06107495,
-0.06127104,
-0.06144379,
-0.06159359,
-0.0617204,
-0.06182358,
-0.06190377,
-0.06196065,
-0.06199473,
-0.062006,
-0.06199472,
-0.0619609,
-0.06190491,
-0.06182672,
-0.06172639,
-0.0616045,
-0.06146098,
-0.06129591,
-0.06110977,
-0.06090261,
-0.06067446,
-0.06042599,
-0.06015691,
-0.05986782,
-0.05955891,
-0.0592304,
-0.05888242,
-0.05851537,
-0.05812925,
-0.05772471,
-0.05730183,
-0.05686083,
-0.0564019,
-0.05592587,
-0.05543222,
-0.05492178,
-0.05439486,
-0.05385128,
-0.05329211,
-0.05271697,
-0.05212655,
-0.05152076,
-0.0509005,
-0.05026548,
-0.0496167,
-0.0489539,
-0.04827756,
-0.04758817,
-0.04688593,
-0.04617106,
-0.04544418,
-0.04470609,
-0.0439575,
-0.04319925,
-0.04243114,
-0.04165368,
-0.04086704,
-0.04007167,
-0.03926748,
-0.03845514,
-0.0376344,
-0.03680612,
-0.03597021,
-0.03512692,
-0.03427665,
-0.03341989,
-0.03255632,
-0.03168911,
-0.03082187,
-0.02995471,
-0.02908867,
-0.02822394,
-0.02736117,
-0.02650031,
-0.02564271,
-0.02478806,
-0.02393765,
-0.0230912,
-0.02224954,
-0.02141314,
-0.02058229,
-0.01975758,
-0.01893955,
-0.01812868,
-0.01732505,
-0.01652964,
-0.01574239,
-0.01496407,
-0.01419478,
-0.0134355,
-0.01268601,
-0.01194714,
-0.01121887,
-0.01050224,
-0.009797051,
-0.009103794,
-0.008423158,
-0.007755322,
-0.007100383,
-0.006458848,
-0.005831254,
-0.005217578,
-0.004618404,
-0.004034016,
-0.00346485,
-0.002910474,
-0.002372103,
-0.001849412,
-0.001343068,
-0.000852818,
-0.00037937,
7.73282E-05,
0.000517061,
0.000939541,
0.001344501,
0.001731659,
};

const float translateY[] = {
0.06560466,
0.08503336,
0.08454602,
0.08401524,
0.08346941,
0.08293103,
0.08240024,
0.08187775,
0.0813631,
0.08085673,
0.08035958,
0.07987116,
0.079392,
0.07892273,
0.07846314,
0.07801378,
0.07757582,
0.07715484,
0.07675322,
0.07637113,
0.07600915,
0.0756675,
0.0756675,
0.07534657,
0.07504655,
0.07476766,
0.07451022,
0.07427509,
0.07406177,
0.07387121,
0.07370363,
0.07355892,
0.07343681,
0.07333811,
0.07326226,
0.07320955,
0.07318028,
0.07317442,
0.07319231,
0.07323403,
0.07329986,
0.07338957,
0.07350334,
0.07364186,
0.07379233,
0.07393147,
0.07405832,
0.07417371,
0.07427747,
0.07437097,
0.07445422,
0.07452733,
0.07459132,
0.07464642,
0.07469305,
0.07473227,
0.07476424,
0.07478917,
0.07480834,
0.07482193,
0.07483026,
0.07483461,
0.07483481,
0.07483211,
0.0748264,
0.07481891,
0.07481024,
0.07480086,
0.07479123,
0.07478189,
0.07477368,
0.07476763,
0.07476377,
0.07476272,
0.07476604,
0.07477321,
0.07478373,
0.07478668,
0.07477971,
0.07476412,
0.07474094,
0.07471138,
0.07467698,
0.07463862,
0.07459759,
0.07455475,
0.07451184,
0.07446972,
0.07442965,
0.07439233,
0.07436004,
0.07433292,
0.07431217,
0.07429925,
0.07429562,
0.07430151,
0.07431879,
0.07434766,
0.07439036,
0.07444739,
0.07451939,
0.07460763,
0.07471299,
0.07483002,
0.0749566,
0.07509428,
0.07524416,
0.0754061,
0.07558155,
0.0757705,
0.07597477,
0.07619398,
0.07642944,
0.07668117,
0.07695062,
0.07722091,
0.07746278,
0.07767648,
0.07786242,
0.07802007,
0.07815032,
0.07825294,
0.07832905,
0.0783779,
0.07840069,
0.07839669,
0.0783675,
0.07831237,
0.07823191,
0.07812621,
0.07799607,
0.07782909,
0.07760733,
0.07733127,
0.0770017,
0.07661973,
0.07618587,
0.07570147,
0.07516754,
0.07458484,
0.07395538,
0.07327827,
0.0725562,
0.07178993,
0.07097995,
0.0701277,
0.06923457,
0.06830109,
0.06732861,
0.06631856,
0.06527167,
0.06418899,
0.06307164,
0.061921,
0.06073842,
0.05952407,
0.05828039,
0.05700741,
0.05570686,
0.05437981,
0.05302692,
0.0516498,
0.05024923,
0.0488265,
0.04738305,
0.04591969,
0.04443748,
0.04293745,
0.04142052,
0.03988818,
0.03834114,
0.03678068,
0.03520793,
0.03362349,
0.03202844,
0.03042478,
0.02881205,
0.02719207,
0.0255656,
0.02393343,
0.02231555,
0.02074416,
0.01921983,
0.01774203,
0.0163039,
0.01491234,
0.01357757,
0.01230091,
0.01108357,
0.009925889,
0.008827634,
0.00779038,
0.006813967,
0.00589917,
0.005045463,
0.004254,
0.003524564,
0.002857289,
0.002252225,
0.001708969,
0.001227986,
0.000808762,
0.000451396,
0.000155284,
-8.02084E-05,
-0.000254649,
-0.000369685,
-0.00042601,
-0.000426555,
-0.000371443,
-0.000261059,
-9.594E-05,
0.000125284,
0.000414197,
0.000772809,
0.001201876,
0.001699935,
0.002267837,
0.002903933,
0.003607967,
0.004379348,
0.005217747,
0.006121628,
0.007089337,
0.008113868,
0.009193406,
0.01032619,
0.0115115,
0.01274762,
0.01403372,
0.01536836,
0.01674969,
0.01817685,
0.01964751,
0.02115904,
0.02270782,
0.02429117,
0.02590764,
0.0275559,
0.02923032,
0.03089782,
0.03254817,
0.03418048,
0.03579285,
0.03738412,
0.0389527,
0.04049703,
0.04201601,
0.04350801,
0.0449715,
0.04640467,
0.04780622,
0.04917491,
0.05050894,
0.05180723,
0.05306707,
0.05428812,
0.05546842,
0.05660595,
0.05767183,
0.05866014,
0.05958873,
0.06045619,
0.06126165,
0.06200321,
0.06268048,
0.06329225,
0.06383714,
0.0643144,
0.06472236,
0.06506038,
0.06532775,
0.06552426,
0.06565035,
0.06570651,
0.06569134,
0.06560466,
0.06545066,
0.06523431,
0.06495474,
0.06461282,
0.06420829,
0.06374118,
0.06321171,
0.06261972,
0.06196649,
0.06125112,
0.06047422,
0.05963626,
0.05873774,
};

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader zprogram
    // ------------------------------------
    Shader noiseShader("../../src/7.in_practice/5.music_effect/7.5.noise.vs", "../../src/7.in_practice/5.music_effect/7.5.noise.fs"); 
    Shader circleShader("../../src/7.in_practice/5.music_effect/7.5.circle.vs", "../../src/7.in_practice/5.music_effect/7.5.circle.fs");
    Shader diplacementMappingShader("../../src/7.in_practice/5.music_effect/7.5.displacement_mapping.vs", "../../src/7.in_practice/5.music_effect/7.5.displacement_mapping.fs");
    Shader feedbackShader("../../src/7.in_practice/5.music_effect/7.5.feedback.vs", "../../src/7.in_practice/5.music_effect/7.5.feedback.fs");
    Shader blurShader("../../src/7.in_practice/5.music_effect/7.5.blur.vs", "../../src/7.in_practice/5.music_effect/7.5.blur.fs");
    Shader colorEnhanceShader("../../src/7.in_practice/5.music_effect/7.5.color_enhance.vs", "../../src/7.in_practice/5.music_effect/7.5.color_enhance.fs");
    Shader diplacementMappingShader2("../../src/7.in_practice/5.music_effect/7.5.displacement_mapping2.vs", "../../src/7.in_practice/5.music_effect/7.5.displacement_mapping2.fs");
    Shader screenShader("../../src/7.in_practice/5.music_effect/7.5.screen.vs", "../../src/7.in_practice/5.music_effect/7.5.screen.fs"); 
    Shader transparentShader("../../src/7.in_practice/5.music_effect/7.5.transparent.vs", "../../src/7.in_practice/5.music_effect/7.5.transparent.fs"); 

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // colors           // texture coords
         1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
        1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
        1.0f, -1.0f,  1.0f, 0.0f,
        1.0f,  1.0f,  1.0f, 1.0f
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // screen quad VAO
    unsigned int quadVAO, quadVBO;
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));


    // load and create a texture 
    // -------------------------
    unsigned int simplex2DNoiseTexture;
    glGenTextures(1, &simplex2DNoiseTexture);
    glBindTexture(GL_TEXTURE_2D, simplex2DNoiseTexture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load(FileSystem::getPath("resources/textures/simplex2DNoise.png").c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // noise framebuffer configuration
    // -------------------------
    unsigned int noisebuffer;
    glGenFramebuffers(1, &noisebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, noisebuffer);
    // create a color attachment texture
    unsigned int noiseTexture;
    glGenTextures(1, &noiseTexture);
    glBindTexture(GL_TEXTURE_2D, noiseTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, noiseTexture, 0);
    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    unsigned int rboNoise;
    glGenRenderbuffers(1, &rboNoise);
    glBindRenderbuffer(GL_RENDERBUFFER, rboNoise);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboNoise); // now actually attach it
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // circle framebuffer configuration
    // -------------------------
    unsigned int circlebuffer;
    glGenFramebuffers(1, &circlebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, circlebuffer);
    // create a color attachment texture
    unsigned int circleTexture;
    glGenTextures(1, &circleTexture);
    glBindTexture(GL_TEXTURE_2D, circleTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, circleTexture, 0);
    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    unsigned int rboCircle;
    glGenRenderbuffers(1, &rboCircle);
    glBindRenderbuffer(GL_RENDERBUFFER, rboCircle);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboCircle); // now actually attach it
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // displacement mapping framebuffer configuration
    // -------------------------
    unsigned int displacementbuffer;
    glGenFramebuffers(1, &displacementbuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, displacementbuffer);
    // create a color attachment texture
    unsigned int displacementTexture;
    glGenTextures(1, &displacementTexture);
    glBindTexture(GL_TEXTURE_2D, displacementTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, displacementTexture, 0);
    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    unsigned int rboDisplacement;
    glGenRenderbuffers(1, &rboDisplacement);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDisplacement);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboDisplacement); // now actually attach it
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // displacement mapping framebuffer configuration
    // -------------------------
    unsigned int displacementbuffer2;
    glGenFramebuffers(1, &displacementbuffer2);
    glBindFramebuffer(GL_FRAMEBUFFER, displacementbuffer2);
    // create a color attachment texture
    unsigned int displacementTexture2;
    glGenTextures(1, &displacementTexture2);
    glBindTexture(GL_TEXTURE_2D, displacementTexture2);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, displacementTexture2, 0);
    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    unsigned int rboDisplacement2;
    glGenRenderbuffers(1, &rboDisplacement2);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDisplacement2);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboDisplacement2); // now actually attach it
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // feedback framebuffer configuration
    // -------------------------
    unsigned int feedbackbuffer;
    glGenFramebuffers(1, &feedbackbuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, feedbackbuffer);
    // create a color attachment texture
    unsigned int feedbackTexture;
    glGenTextures(1, &feedbackTexture);
    glBindTexture(GL_TEXTURE_2D, feedbackTexture);
    void* emptyData = malloc(SCR_WIDTH * SCR_HEIGHT * sizeof(char) * 4);
    memset(emptyData, 1, SCR_WIDTH * SCR_HEIGHT * sizeof(char) * 4);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, emptyData);
    // glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, feedbackTexture, 0);

    // 
    unsigned int feedbackTextureBack;
    glGenTextures(1, &feedbackTextureBack);
    glBindTexture(GL_TEXTURE_2D, feedbackTextureBack);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, emptyData);
    // glGenerateMipmap(GL_TEXTURE_2D);
    free(emptyData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, feedbackTexture, 0);

    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    unsigned int rboFeedback;
    glGenRenderbuffers(1, &rboFeedback);
    glBindRenderbuffer(GL_RENDERBUFFER, rboFeedback);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboFeedback); // now actually attach it
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // blur framebuffer configuration
    // -------------------------
    int preShrink = 1.0;
    unsigned int blurBuffer;
    glGenFramebuffers(1, &blurBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, blurBuffer);
    // create a color attachment texture
    unsigned int blurTexture;
    glGenTextures(1, &blurTexture);
    glBindTexture(GL_TEXTURE_2D, blurTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, blurTexture, 0);
    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    unsigned int rboBlur;
    glGenRenderbuffers(1, &rboBlur);
    glBindRenderbuffer(GL_RENDERBUFFER, rboBlur);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboBlur); // now actually attach it
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // blur framebuffer configuration
    // -------------------------
    unsigned int transparentBuffer;
    glGenFramebuffers(1, &transparentBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, transparentBuffer);
    // create a color attachment texture
    unsigned int transparentTexture;
    glGenTextures(1, &transparentTexture);
    glBindTexture(GL_TEXTURE_2D, transparentTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, transparentTexture, 0);
    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    unsigned int rboTransparent;
    glGenRenderbuffers(1, &rboTransparent);
    glBindRenderbuffer(GL_RENDERBUFFER, rboTransparent);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboTransparent); // now actually attach it
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // color enhance framebuffer configuration
    // -------------------------
    unsigned int colorEnhanceBuffer;
    glGenFramebuffers(1, &colorEnhanceBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, colorEnhanceBuffer);
    // create a color attachment texture
    unsigned int colorEnhanceTexture;
    glGenTextures(1, &colorEnhanceTexture);
    glBindTexture(GL_TEXTURE_2D, colorEnhanceTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorEnhanceTexture, 0);
    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    unsigned int rboColorEnhance;
    glGenRenderbuffers(1, &rboColorEnhance);
    glBindRenderbuffer(GL_RENDERBUFFER, rboColorEnhance);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboColorEnhance); // now actually attach it
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    int blurRadius = 9;
    float sigma = float(blurRadius) / 3.0;
    float sumWeight = 0.0;
    for (int i = 0; i < blurRadius; i++) {
        float weight = (float)((1.0 / sqrt(2.0 * M_PI * sigma *sigma)) * exp(-(float(i) * float(i)) / (2.0 * sigma * sigma)));
        sumWeight += weight;
        if (i != 0) {
            sumWeight += weight;
        }
    }
    printf("weight: %f\n", sumWeight);


    // render loop
    // -----------
    int frame = 0;
    srand((int)glfwGetTime());
    while (!glfwWindowShouldClose(window))
    {
        double time = (double)glfwGetTime();
        printf("time :%f, frame: %d\n",time ,frame);
        // input
        // -----
        processInput(window);

        // render noise begin --------------------------------------------------------------------------------------------
        // bind to framebuffer and draw scene as we normally would to color texture 
        glBindFramebuffer(GL_FRAMEBUFFER, noisebuffer);
        glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

        // make sure we clear the framebuffer's content
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render container
        noiseShader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
        // clear all relevant buffers
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
        glClear(GL_COLOR_BUFFER_BIT);
        // render noise end -----------------------------------------------------------------------------------------------

        // render circle begin --------------------------------------------------------------------------------------------
        // bind to framebuffer and draw scene as we normally would to color texture 
        glBindFramebuffer(GL_FRAMEBUFFER, circlebuffer);
        glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

        // make sure we clear the framebuffer's content
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render container
        circleShader.use();
        {
            circleShader.setFloat("centerX", 0.5 + translateX[int(time * 60) % 290]);
            circleShader.setFloat("centerY", 0.5 + translateY[int(time * 60) % 290]);
            circleShader.setFloat("radius", radiuss[int(time * 60) % 200]);
            circleShader.setFloat("hue", sin(time));
            circleShader.setFloat("time", time);
        }


        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
        // clear all relevant buffers
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
        glClear(GL_COLOR_BUFFER_BIT);
        // render circle end ----------------------------------------------------------------------------------------------

        // render displacement mapping begin --------------------------------------------------------------------------------------------
        // bind to framebuffer and draw scene as we normally would to color texture 
        glBindFramebuffer(GL_FRAMEBUFFER, displacementbuffer);
        glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

        // make sure we clear the framebuffer's content
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render container
        diplacementMappingShader.use();
        {
            diplacementMappingShader.setInt("noiseTexture", 0);
            diplacementMappingShader.setInt("circleTexture", 1);
        }
        glBindVertexArray(VAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, simplex2DNoiseTexture);
        glActiveTexture(GL_TEXTURE0 + 1);
        glBindTexture(GL_TEXTURE_2D, circleTexture);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
        // clear all relevant buffers
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
        glClear(GL_COLOR_BUFFER_BIT);
        // render displacement mapping end ----------------------------------------------------------------------------------------------


        // render transparent begin --------------------------------------------------------------------------------------------
        // bind to framebuffer and draw scene as we normally would to color texture 
        glBindFramebuffer(GL_FRAMEBUFFER, transparentBuffer);
        glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

        // make sure we clear the framebuffer's content
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render container
        transparentShader.use();
        {
            transparentShader.setInt("transparentTexture", 0);
        }
        glBindVertexArray(VAO);
        glActiveTexture(GL_TEXTURE0);
        if (frame == 0) {
            glBindTexture(GL_TEXTURE_2D, displacementTexture);
        } else {
            glBindTexture(GL_TEXTURE_2D, feedbackTexture);
        }
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
        // clear all relevant buffers
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
        glClear(GL_COLOR_BUFFER_BIT);
        // render transparent end ----------------------------------------------------------------------------------------------

        // render feedback begin --------------------------------------------------------------------------------------------
        // bind to framebuffer and draw scene as we normally would to color texture 
        glBindFramebuffer(GL_FRAMEBUFFER, feedbackbuffer);
        // if (frame % 2 == 0) {
        //     glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, feedbackTexture, 0);
        // } else {
        //     glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, feedbackTextureBack, 0);
        // }
        glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

        // make sure we clear the framebuffer's content
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render container
        feedbackShader.use();
        {
            feedbackShader.setInt("feedbackTexture", 0);
            feedbackShader.setInt("circleMappingTexture", 1);
        }
        glBindVertexArray(VAO);
        // if (frame % 2 == 0) {
        //     glActiveTexture(GL_TEXTURE0);
        //     glBindTexture(GL_TEXTURE_2D, feedbackTextureBack);
        // } else {
        //     glActiveTexture(GL_TEXTURE0);
        //     glBindTexture(GL_TEXTURE_2D, feedbackTexture);
        // }
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, transparentTexture);
        glActiveTexture(GL_TEXTURE0 + 1);
        glBindTexture(GL_TEXTURE_2D, displacementTexture);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
        // clear all relevant buffers
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
        glClear(GL_COLOR_BUFFER_BIT);
        // render feedback end ----------------------------------------------------------------------------------------------

        // // render blur begin --------------------------------------------------------------------------------------------
        // // bind to framebuffer and draw scene as we normally would to color texture 
        // glBindFramebuffer(GL_FRAMEBUFFER, blurBuffer);
        // glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

        // // make sure we clear the framebuffer's content
        // glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // // render container
        // blurShader.use();
        // {
        //     blurShader.setInt("inTexture", 0);
        // }
        // glBindVertexArray(VAO);
        // glActiveTexture(GL_TEXTURE0);
        // if (frame % 2 == 0) {
        //     glBindTexture(GL_TEXTURE_2D, feedbackTexture);
        // } else {
        //     glBindTexture(GL_TEXTURE_2D, feedbackTextureBack);
        // }
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0);

        // // now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
        // glBindFramebuffer(GL_FRAMEBUFFER, 0);
        // glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
        // // clear all relevant buffers
        // glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
        // glClear(GL_COLOR_BUFFER_BIT);
        // // render blur end ----------------------------------------------------------------------------------------------


        // render color enhance begin --------------------------------------------------------------------------------------------
        // bind to framebuffer and draw scene as we normally would to color texture 
        glBindFramebuffer(GL_FRAMEBUFFER, colorEnhanceBuffer);
        glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

        // make sure we clear the framebuffer's content
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render container
        colorEnhanceShader.use();
        {
            colorEnhanceShader.setInt("feedbackTexture", 0);
        }
        glBindVertexArray(VAO);
        glActiveTexture(GL_TEXTURE0);
        // if (frame % 2 == 0) {
        //     glBindTexture(GL_TEXTURE_2D, feedbackTexture);
        // } else {
        //     glBindTexture(GL_TEXTURE_2D, feedbackTextureBack);
        // }
        glBindTexture(GL_TEXTURE_2D, feedbackTexture);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
        // clear all relevant buffers
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
        glClear(GL_COLOR_BUFFER_BIT);
        // render color enhance end ----------------------------------------------------------------------------------------------

        // // render blur begin --------------------------------------------------------------------------------------------
        // // bind to framebuffer and draw scene as we normally would to color texture 
        // glBindFramebuffer(GL_FRAMEBUFFER, blurBuffer);
        // glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

        // // make sure we clear the framebuffer's content
        // glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // // render container
        // blurShader.use();
        // {
        //     blurShader.setInt("inTexture", 0);
        // }
        // glBindVertexArray(VAO);
        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D, colorEnhanceTexture);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0);

        // // now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
        // glBindFramebuffer(GL_FRAMEBUFFER, 0);
        // glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
        // // clear all relevant buffers
        // glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
        // glClear(GL_COLOR_BUFFER_BIT);
        // // render blur end ----------------------------------------------------------------------------------------------

        // render displacement mapping begin --------------------------------------------------------------------------------------------
        // bind to framebuffer and draw scene as we normally would to color texture 
        glBindFramebuffer(GL_FRAMEBUFFER, displacementbuffer2);
        glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

        // make sure we clear the framebuffer's content
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render container
        diplacementMappingShader2.use();
        {
            diplacementMappingShader2.setInt("noiseTexture", 0);
            diplacementMappingShader2.setInt("circleTexture", 1);
            diplacementMappingShader2.setFloat("time", time / 40.0);
        }
        glBindVertexArray(VAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, colorEnhanceTexture);
        glActiveTexture(GL_TEXTURE0 + 1);
        // if (frame % 2 == 0) {
        //     glBindTexture(GL_TEXTURE_2D, feedbackTexture);
        // } else {
        //     glBindTexture(GL_TEXTURE_2D, feedbackTextureBack);
        // }
        glBindTexture(GL_TEXTURE_2D, feedbackTexture);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
        // clear all relevant buffers
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
        glClear(GL_COLOR_BUFFER_BIT);
        // render displacement mapping end ----------------------------------------------------------------------------------------------

        // render screen
        // -------------------------------------------------------------------------------------------------
        screenShader.use();
        {
            screenShader.setInt("screenTexture", 0);
        }
        glBindVertexArray(quadVAO);
        glActiveTexture(GL_TEXTURE0);
        // use the color attachment texture as the texture of the quad plane
        glBindTexture(GL_TEXTURE_2D, displacementTexture2);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
        frame++;
        // sleep(1);
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
