using namespace std;
//#define OP operator
//#define STI static inline
//#define FOR0(i,n) for(int i=0;i<(n);++i)
typedef long long ll

/* //{PRINT BITS
STI std::array<string,256> loadstr_byte(){std::array<string,256>l;FOR0(i,256){l[i]="";for(int j=7;j>=0;--j)l[i]+=to_string((i>>j)&1);}return l;}
std::array<string,256> str_byte=loadstr_byte();
STI string printbits(const uint8_t& p){return str_byte[(uint8_t)p];}
//}*/

//{Stopwatch
 #define TIMEOUT0_0 400000 
 #define TIMEOUT0_1 980000 
 #define TIMEOUTN_0 22000  
 #define TIMEOUTN_1 46500  
 #define Now() std::chrono::high_resolution_clock::now()
static struct Stopwatch {
	std::chrono::high_resolution_clock::time_point c_time,c_timeout;
	void Start() {c_time=Now();}
	void setTimeout(int us){c_timeout=c_time+std::chrono::microseconds(us);}
	inline bool Timeout(){return Now()>c_timeout;}
	ll EllapsedMicroseconds(){return std::chrono::duration_cast<chrono::microseconds>(Now()-c_time).count();}
	ll EllapsedMilliseconds(){return std::chrono::duration_cast<chrono::milliseconds>(Now()-c_time).count();}
} stopwatch;
//}

//{ Vector 8xfloat  <-> 8xshort conversion
STI v8f convert(const v8i& vector_int)  //8xint16_t to 8xfloat
{
 __m128 ALIGN16 lo = _mm_cvtepi32_ps(_mm_cvtepi16_epi32(vector_int.v));
 __m128 ALIGN16 hi = _mm_cvtepi32_ps(_mm_cvtepi16_epi32(_mm_srli_si128(vector_int.v, 8)));
 return _mm256_insertf128_ps(_mm256_castps128_ps256(lo),(hi),1);
}

STI v8i convert(const v8f& vector_float) //8xfloat to 8xint16_t
{
 __m128i ALIGN16 lo =  _mm_cvtps_epi32(_mm256_castps256_ps128(vector_float.v));
 __m128i ALIGN16 hi =  _mm_cvtps_epi32(_mm256_extractf128_ps(vector_float.v,1));
  return _mm_packs_epi32(lo,hi);
}
//}

//{FAST RANDOM
constexpr int RND_SEED=8000;
static unsigned int g_seed=RND_SEED;
inline int fastrand() {	g_seed = (214013 * g_seed + 2531011);return (g_seed >> 16) & 0x7FFF;}
inline int fastRandInt(int maxSize) {return fastrand() % maxSize;}
inline int fastRandInt(int a, int b) {return(a + fastRandInt(b - a));}
inline float fastRandDouble(){return static_cast<float>(fastrand())/0x7FFF;}
inline float fastRandDouble(float a,float b){return a+(static_cast<float>(fastrand())/0x7FFF)*(b-a);}
//}FAST RANDOM
//{FAST RANDOM VECTORIZED
#pragma GCC diagnostic ignored "-Wnarrowing"
__m128i SEED_RANDOM={UINT64_C(2000),UINT64_C(8000)};
static const __m128i v2i_k1 = {UINT64_C(0x9E3779B97F4A7C15),UINT64_C(0x9E3779B97F4A7C15)};
static const __m128i v2i_k2 = {UINT64_C(0xBF58476D1CE4E5B9),UINT64_C(0xBF58476D1CE4E5B9)};
static const __m128i v2i_k3 = {UINT64_C(0x94D049BB133111EB),UINT64_C(0x94D049BB133111EB)};
static const __m128i v2i_k4 = {2685821657736338717LL,2685821657736338717LL};
static const __m128i v2i_9  = {UINT64_C(9),UINT64_C(9)};
static const __m128i v2i_27 = {UINT64_C(27),UINT64_C(27)};
static const __m128i v2i_28 = {UINT64_C(28),UINT64_C(28)};
static const __m128i v2i_30 = {UINT64_C(30),UINT64_C(30)};
static const __m128i v2i_31 = {UINT64_C(31),UINT64_C(31)};
static const __m128i v2i_55 = {UINT64_C(55),UINT64_C(55)};
static const __m128i v2i_36 = {UINT64_C(36),UINT64_C(36)};
static const __m128i v2i_12 = {UINT64_C(12),UINT64_C(12)};
static const __m128i v2i_14 = {UINT64_C(14),UINT64_C(14)};
static const __m128i v2i_25 = {UINT64_C(25),UINT64_C(25)};
static const __m128i v8i_FF = {UINT64_C(0xFFFFFFFFFFFFFFFF),UINT64_C(0xFFFFFFFFFFFFFFFF)};
static const __m128i v8i_UINT={UINT64_C(0x7FFF7FFF7FFF7FFF),UINT64_C(0x7FFF7FFF7FFF7FFF)};
static const __m128i v8i_UB = {UINT64_C(0x7F7F7F7F7F7F7F7F),UINT64_C(0x7F7F7F7F7F7F7F7F)};

inline __m128i mul64(__m128i const & a,__m128i const & b){
    __m128i bswap   = _mm_shuffle_epi32(b,0xB1);           // b0H,b0L,b1H,b1L (swap H<->L)
    __m128i prodlh  = _mm_mullo_epi32(a,bswap);            // a0Lb0H,a0Hb0L,a1Lb1H,a1Hb1L, 32 bit L*H products
    __m128i zero    = _mm_setzero_si128();                 // 0
    __m128i prodlh2 = _mm_hadd_epi32(prodlh,zero);         // a0Lb0H+a0Hb0L,a1Lb1H+a1Hb1L,0,0
    __m128i prodlh3 = _mm_shuffle_epi32(prodlh2,0x73);     // 0, a0Lb0H+a0Hb0L, 0, a1Lb1H+a1Hb1L
    __m128i prodll  = _mm_mul_epu32(a,b);                  // a0Lb0L,a1Lb1L, 64 bit unsigned products
    __m128i prod    = _mm_add_epi64(prodll,prodlh3);       // a0Lb0L+(a0Lb0H+a0Hb0L)<<32, a1Lb1L+(a1Lb1H+a1Hb1L)<<32
    return  prod;    
}

__m128i xnext() {
    SEED_RANDOM = _mm_add_epi64(SEED_RANDOM,v2i_k1);
    __m128i ALIGN16 z = SEED_RANDOM;
	z=mul64(_mm_xor_si128(z,_mm_srl_epi64(z,v2i_30)),v2i_k2);
	z=mul64(_mm_xor_si128(z,_mm_srl_epi64(z,v2i_27)),v2i_k3);
	return _mm_xor_si128(z,_mm_srl_epi64(z,v2i_31));
}
__m128i ALIGN16 seed[2]={ xnext(),xnext() };

inline __m128i Xrandom() {
	__m128i ALIGN16 s0=seed[0];
	__m128i ALIGN16 s1=seed[1];
	__m128i ALIGN16 result=_mm_add_epi64(s0,s1);
	s1= _mm_xor_si128(s1,s0);
	seed[0]=_mm_xor_si128(_mm_or_si128(_mm_sll_epi64(s0,v2i_55),_mm_srl_epi64(s1,v2i_9)),_mm_xor_si128(s1,_mm_sll_epi64(s1,v2i_14)));
	seed[1]=_mm_or_si128(_mm_sll_epi64(s1,v2i_36),_mm_srl_epi64(s1,v2i_28));
	return result;
}

#if INT_TYPE ==1
  inline __m128i Brandom(){return _mm_and_si128(Xrandom(),v8i_UB);}

 template <int i0>
 inline __m128i Brandom(){
   switch(i0) {   
     case 2:case 4:case 8:case 16:case 32:case 64:case 128:case 256:
      return _mm_and_si128(Xrandom(),C_B<i0-1>());
    default: break;
   }  
   union {__m128i ALIGN16 v;int8_t f[B_SIZE];} h;
   h.v = _mm_and_si128(Xrandom(),v8i_UB);
   FOR0(j,B_SIZE) h.f[j] = (int8_t)(h.f[j]%i0);
   return h.v;
 }
 template <int init,int end>
 inline __m128i Brandom(){ return _mm_adds_epi8(Brandom<end-init>(),_mm_set1_epi8(init)); }
 inline __m128i Brandom(int i0){
   switch(i0) {   
     case 2:case 4:case 8:case 16:case 32:case 64:case 128:case 256:
      return _mm_and_si128(Xrandom(),_mm_set1_epi8((int8_t)(i0-1)));
    default: break;
   }  
   union {__m128i ALIGN16 v;int8_t f[B_SIZE];} h;
   h.v = _mm_and_si128(Xrandom(),v8i_UB);
   FOR0(j,B_SIZE) h.f[j] = (int8_t)(h.f[j]%i0);
   return h.v;
 }
 inline __m128i Brandom(int init,int end){ return Brandom(end-init)+init;}
 inline __m128i BrandomBool(){return _mm_cmpeq_epi8(_mm_and_si128(Xrandom(),B_1.v), B_0);}
 
 inline __m128i Irandom(){return _mm_and_si128(Xrandom(),v8i_UINT);}
 template <int i0>
 inline __m128i Irandom(){
switch(i0) {   
 case 2:case 4:case 8:case 16:case 32:case 64:case 128:case 256:case 512:case 1024:

  static const union {int16_t f[8];__m128i v;} u = {{(int16_t)(i0-1),(int16_t)(i0-1),(int16_t)(i0-1),(int16_t)(i0-1)
                                                    ,(int16_t)(i0-1),(int16_t)(i0-1),(int16_t)(i0-1),(int16_t)(i0-1)}};
    return _mm_and_si128(Xrandom(),u.v);
 default: break;
}  
     
//Slower calculation     
   #if FLOAT_TYPE ==1
    __m256 ALIGN a = convert(_mm_and_si128(Xrandom(),v8i_UINT));
    __m256 ALIGN den = _mm256_set1_ps((float)i0);
    __m256 ALIGN c = _mm256_mul_ps(a,_mm256_set1_ps(1.0f/(float)i0));
    __m256 ALIGN base = _mm256_mul_ps(_mm256_round_ps(c,3+8),den);
    return convert(_mm256_sub_ps(a, base));
 #else
   union {__m128i ALIGN16 v;int16_t f[8];} h;
   h.v = _mm_and_si128(Xrandom(),v8i_UINT);
   FOR0(j,8) h.f[j] = (int16_t)(h.f[j]%i0);
   return h.v;
 #endif
 }
 template <int init,int end>
 inline __m128i Irandom(){
switch(end-init) {   
 case 2:case 4:case 8:case 16:case 32:case 64:case 128:case 256:case 512:case 1024:

  static const union {int16_t f[8];__m128i v;} u = {{(int16_t)(end-init-1),(int16_t)(end-init-1),(int16_t)(end-init-1),(int16_t)(end-init-1)
                                                    ,(int16_t)(end-init-1),(int16_t)(end-init-1),(int16_t)(end-init-1),(int16_t)(end-init-1)}};
    return _mm_add_epi16(_mm_and_si128(Xrandom(),u.v),_mm_set1_epi16(init));
 default: break;
}          
   #if FLOAT_TYPE ==1
    __m256 ALIGN a = convert(_mm_and_si128(Xrandom(),v8i_UINT));
    __m256 ALIGN den = _mm256_set1_ps((float)(end-init));
    __m256 ALIGN c = _mm256_mul_ps(a,_mm256_set1_ps(1.0f/(float)(end-init)));
    __m256 ALIGN base = _mm256_mul_ps(_mm256_round_ps(c,3+8),den);
    return convert(_mm256_add_ps(_mm256_sub_ps(a, base),_mm256_set1_ps((float)init)));
   #else
     union {__m128i ALIGN16 v;int16_t f[8];} h;
     h.v = _mm_and_si128(Xrandom(),v8i_UINT);
     FOR0(j,8) h.f[j] = (int16_t)(init+h.f[j]%(end-init));
     return h.v;   
   #endif 
 }
 inline __m128i Irandom(const int& i0){
switch(i0) {   
 case 2:case 4:case 8:case 16:case 32:case 64:case 128:case 256:case 512:case 1024:

  static const union {int16_t f[8];__m128i v;} u = {{(int16_t)(i0-1),(int16_t)(i0-1),(int16_t)(i0-1),(int16_t)(i0-1)
                                                    ,(int16_t)(i0-1),(int16_t)(i0-1),(int16_t)(i0-1),(int16_t)(i0-1)}};
    return _mm_and_si128(Xrandom(),u.v);
 default: break;
}  
     
//Slower calculation     
   #if FLOAT_TYPE ==1
    __m256 ALIGN a = convert(_mm_and_si128(Xrandom(),v8i_UINT));
    __m256 ALIGN den = _mm256_set1_ps((float)i0);
    __m256 ALIGN c = _mm256_mul_ps(a,_mm256_set1_ps(1.0f/(float)i0));
    __m256 ALIGN base = _mm256_mul_ps(_mm256_round_ps(c,3+8),den);
    return convert(_mm256_sub_ps(a, base));
 #else
   union {__m128i ALIGN16 v;int16_t f[8];} h;
   h.v = _mm_and_si128(Xrandom(),v8i_UINT);
   FOR0(j,8) h.f[j] = (int16_t)(h.f[j]%i0);
   return h.v;
 #endif
 }
 inline __m128i Irandom(const int& init,const int& end){
switch(end-init) {   
 case 2:case 4:case 8:case 16:case 32:case 64:case 128:case 256:case 512:case 1024:

    static const union {int16_t f[8];__m128i v;} u = {{(int16_t)(end-init-1),(int16_t)(end-init-1),(int16_t)(end-init-1),(int16_t)(end-init-1)
                                                    ,(int16_t)(end-init-1),(int16_t)(end-init-1),(int16_t)(end-init-1),(int16_t)(end-init-1)}};
    return _mm_add_epi16(_mm_and_si128(Xrandom(),u.v),_mm_set1_epi16(init));
 default: break;
}          
   #if FLOAT_TYPE ==1
    __m256 ALIGN a = convert(_mm_and_si128(Xrandom(),v8i_UINT));
    __m256 ALIGN den = _mm256_set1_ps((float)(end-init));
    __m256 ALIGN c = _mm256_mul_ps(a,_mm256_set1_ps(1.0f/(float)(end-init)));
    __m256 ALIGN base = _mm256_mul_ps(_mm256_round_ps(c,3+8),den);
    return convert(_mm256_add_ps(_mm256_sub_ps(a, base),_mm256_set1_ps((float)init)));
   #else
     union {__m128i ALIGN16 v;int16_t f[8];} h;
     h.v = _mm_and_si128(Xrandom(),v8i_UINT);
     FOR0(j,8) h.f[j] = (int16_t)(init+h.f[j]%(end-init));
     return h.v;   
   #endif 
 }
 inline __m128i IrandomBool(){return  _mm_cmpeq_epi16(_mm_and_si128(Xrandom(),I_1.v), I_0);}
#endif

#if FLOAT_TYPE ==1
 inline __m256 Frandom(){
	 return convert(_mm_and_si128(Xrandom(),v8i_UINT));
 }

 template <int i0>
 inline __m256 Frandom(){
switch(i0) {   
 case 2:case 4:case 8:case 16:case 32:case 64:case 128:case 256:case 512:case 1024:

  static const union {int16_t f[8];__m128i v;} u = {{(int16_t)(i0-1),(int16_t)(i0-1),(int16_t)(i0-1),(int16_t)(i0-1)
                                                    ,(int16_t)(i0-1),(int16_t)(i0-1),(int16_t)(i0-1),(int16_t)(i0-1)}};
    return convert(_mm_and_si128(Xrandom(),u.v));
 default: break;
}       
//Slower calculation     
    __m256 ALIGN a = convert(_mm_and_si128(Xrandom(),v8i_UINT));
    __m256 ALIGN den = _mm256_set1_ps((float)i0);
    __m256 ALIGN c = _mm256_mul_ps(a,_mm256_set1_ps(1.0f/(float)i0));
    __m256 ALIGN base = _mm256_mul_ps(_mm256_round_ps(c,3+8),den);
    return _mm256_sub_ps(a, base);
 }
 
 template <int init,int end>
 inline __m256 Frandom(){
switch(end-init) {   
 case 2:case 4:case 8:case 16:case 32:case 64:case 128:case 256:case 512:case 1024:

  static const union {int16_t f[8];__m128i v;} u = {{(int16_t)(end-init-1),(int16_t)(end-init-1),(int16_t)(end-init-1),(int16_t)(end-init-1)
                                                    ,(int16_t)(end-init-1),(int16_t)(end-init-1),(int16_t)(end-init-1),(int16_t)(end-init-1)}};
    return _mm256_add_ps(convert(_mm_and_si128(Xrandom(),u.v)),_mm256_set1_ps((float)init));
 default: break;
}          
    __m256 ALIGN a = convert(_mm_and_si128(Xrandom(),v8i_UINT));
    __m256 ALIGN den = _mm256_set1_ps((float)(end-init));
    __m256 ALIGN c = _mm256_mul_ps(a,_mm256_set1_ps(1.0f/(float)(end-init)));
    __m256 ALIGN base = _mm256_mul_ps(_mm256_round_ps(c,3+8),den);
    return _mm256_add_ps(_mm256_sub_ps(a, base),_mm256_set1_ps((float)init));
 }
 
 inline __m256 Frandom(const int& i0){
    __m256 ALIGN a = convert(_mm_and_si128(Xrandom(),v8i_UINT));
    __m256 ALIGN den = _mm256_set1_ps((float)i0);
    __m256 ALIGN c = _mm256_mul_ps(a,_mm256_set1_ps(1.0f/(float)i0));
    __m256 ALIGN base = _mm256_mul_ps(_mm256_round_ps(c,3+8),den);
    return _mm256_sub_ps(a, base);
 }

 inline __m256 Frandom(const int& init,const int& end){
    __m256 ALIGN a = convert(_mm_and_si128(Xrandom(),v8i_UINT));
    __m256 ALIGN den = _mm256_set1_ps((float)(end-init));
    __m256 ALIGN c = _mm256_mul_ps(a,_mm256_set1_ps(1.0f/(float)(end-init)));
    __m256 ALIGN base = _mm256_mul_ps(_mm256_round_ps(c,3+8),den);
    return _mm256_add_ps(_mm256_sub_ps(a, base),_mm256_set1_ps((float)init));
 }
 
 inline __m256 FrandomBool(){
     static const union {int16_t f[8];__m128i v;} V_1 = {{1,1,1,1,1,1,1,1}};
     return _mm256_cmp_ps(convert(_mm_and_si128(Xrandom(),V_1.v)),F_0,0);
     }
 
#endif
//}FAST RANDOM VECTORIZED


//{ Atan2 approximations
static const ALIGN v8f v8fPI = {(float)M_PI,(float)M_PI,(float)M_PI,(float)M_PI,(float)M_PI,(float)M_PI,(float)M_PI,(float)M_PI};
static const ALIGN v8f v8fHALFPI = {(float)M_PI/2.0,(float)M_PI/2.0,(float)M_PI/2.0,(float)M_PI/2.0,(float)M_PI/2.0,(float)M_PI/2.0,(float)M_PI/2.0,(float)M_PI/2.0};

//Medium precission atan2. 3.5e-5 0.000035  2x accuracy than atan2c
STI v8f atan2(Pv8fab) { //8*83M opers/sec 58x faster than real atan2, 468x faster due to vectorization. 2x precission than atan2c
  v8f ALIGN t0, t1, t2, t3, t4;
  t3 = abs(b);
  t1 = abs(a);
  t0 = max(t3, t1);
  t1 = min(t3, t1);
  t3 = approx_recipr(t0); //approximate
  //t3 = (F_1/t0);
  t3 = t1*t3;
  t4 = t3* t3;
  t0 = v8f(-0.013480470f);
  t0 = ((t0 * t4)+0.057477314f);
  t0 = ((t0 * t4)-0.121239071f);
  t0 = ((t0 * t4)+0.195635925f);
  t0 = ((t0 * t4)-0.332994597f);
  t0 = ((t0 * t4)+0.999995630f);
  t3 = (t0*t3);
  t3= if_select( abs(a)>abs(b), (v8fHALFPI-t3),t3);
  t3= if_select( b<F_0, (v8fPI-t3),t3);
  t3= if_select( a<F_0, (F_0-t3),t3);
  return t3;
}

//Higher precission atan2. 1.2e-6 = 0.0000012 60x accuracy than atan2c, 30x accuracy atan2
STI v8f atan2E(Pv8fab) { //8*62M opers/sec 43x faster than real atan2, 350x faster due to vectorization
  v8f ALIGN t0, t1, t2, t3, t4;
  t3 = abs(b);
  t1 = abs(a);
  t0 = max(t3, t1);
  t1 = min(t3, t1);
  //t3 = approx_recipr(t0); //approximate
  t3 = (F_1/t0);
  t3 = t1*t3;
  t4 = t3* t3;
  t0 = v8f(-0.013480470f);
  t0 = ((t0 * t4)+0.057477314f);
  t0 = ((t0 * t4)-0.121239071f);
  t0 = ((t0 * t4)+0.195635925f);
  t0 = ((t0 * t4)-0.332994597f);
  t0 = ((t0 * t4)+0.999995630f);
  t3 = (t0*t3);
  t3= if_select( abs(a)>abs(b), (v8fHALFPI-t3),t3);
  t3= if_select( b<F_0, (v8fPI-t3),t3);
  t3= if_select( a<F_0, (F_0-t3),t3);
  return t3;
}
//}

template <int i0>
STI v8f fastmodulus(v8f const &a){ //We pass the denominator as 1/b directly, so division was done in compile time
    __m256 ALIGN den = _mm256_set1_ps((float)i0);
    __m256 ALIGN c = _mm256_mul_ps(a.v,_mm256_set1_ps(1.0f/(float)i0));
    __m256 ALIGN base = _mm256_mul_ps(_mm256_round_ps(c,3+8),den);
    return _mm256_sub_ps(a.v, base);
}