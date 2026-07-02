#include <iostream>
#include <cstdint>
#include <limits>
#include <vector>

class LCG{

private:
    static constexpr std::uint64_t LCG_A = 6364136223846793005ULL;
    static constexpr std::uint64_t LCG_C = 1442695040888963407ULL;
    std::uint64_t state;
public:
    // Seed-based LCG for deterministic random generation.
    explicit LCG(std::uint64_t seed) : state(seed){}

    [[nodiscard]] std::uint64_t StateUpdate() noexcept{

        //$$ S_{t+1} = (a \times S_t \space + c) \space (mod \space 2^{64})$$
        state = LCG_A*state + LCG_C;
        return state;
    }
    
    [[nodiscard]] long double NextRandomNumber ( 
        long double v_min,
        long double v_max
    ) noexcept{

        std::uint64_t states_atual = StateUpdate();

        //$$u_t = \frac{S_t}{2^{64}-1}$$

        long double u = static_cast<long double>(states_atual)/(static_cast<long double>(std::numeric_limits<std::uint64_t>::max()));

        //$$ next \space number = V_{min}+(V_{max}-V_{min})\times u_t:next\space number \in [V_{min},V_{max}]$$

        return v_min + (v_max - v_min)*u;
    }

};

class matrix_generation{
    private:
        LCG lcg;
    
    public:

        explicit matrix_generation(std::uint64_t seed) : lcg(seed){}

        [[nodiscard]] std::vector<long double> MatrixGenerationWithLcg(
            int m, 
            int n, 
            long double n_min, 
            long double n_max
        ){
            std::vector<long double> v(m*n);    

            for(int i = 0; i < m; ++i){
                for(int j = 0; j < n; ++j){
                    v[i*n + j] = lcg.NextRandomNumber(n_min, n_max);
                }
            }

            return v;
        } 
};

class multiply{

    public:
        
        [[nodiscard]] long double ElementC (
            const std::vector<long double>& A, 
            const std::vector<long double>& W,
            int p, 
            int n, 
            int current_m, 
            int current_p
        ){

            long double c = 0.0;

            for(int j = 0; j < n; ++j){

                //$$ c_{m,p} \in C_{(m \times p)} : c_{m,p} := \sum_{j=0}^{n-1}a_{m,j} \times w_{j,p}, j<n $$

                c += A[current_m*n + j] * W[j*p + current_p];
            }
            

            return c;

        }

        [[nodiscard]] std::vector<long double> MultiplyMatrix(
            const std::vector<long double>& A, 
            const std::vector<long double>& W, 
            int m, 
            int n, 
            int p
        ){

            //$$  C_{(m \times p)}:= A_{(m \times n)} \times W_{(n \times p)} $$

            std::vector<long double>C(m*p);

            for(int i=0;i<m;++i){
                for(int j=0; j<p;++j){

                    C[i*p + j] = ElementC(A,W,p,n,i,j);

                }
            }

            return C;

        }
};

int main(){

    int m,n,p;
    long double v_min, v_max;
    matrix_generation mg(42);
    multiply mult_matrix;

    //Matrix Multiplication
    //$$ A \in R^{m \times n}$$ and $$ W \in R^{n \times p} $$
    //$$R^{m \times n} \times R^{n \times p} -> R^{m \times p}$$
    // $$C:=A \times W$$

    //Row-major layout:
    // A(i,j) = A[i*n + j]
    // W(j,k) = W[j*p + k]
    // C(i,k) = C[i*p + k]

    std::cout<<"You write in this sequence: (m, n, p, v_min, v_max | m,n,p > 0 & v_max > v_min):\n";

    if (!(std::cin >> m >> n >> p >> v_min >> v_max)) {
        std::cerr << "Error: invalid input.\n";
        return 1;
    }

    if (m <= 0 || n <= 0 || p <= 0) {
        std::cerr << "Error: m, n and p must be positive.\n";
        return 1;
    }

    if (v_max <= v_min) {
        std::cerr << "Error: v_max must be greater than v_min.\n";
        return 1;
    }

    //Matrix generator

    std::vector<long double> A = mg.MatrixGenerationWithLcg(m,n,v_min,v_max);
    std::vector<long double> W = mg.MatrixGenerationWithLcg(n,p,v_min,v_max);

    std::cout<<"\nMultiply Matrix A*W:\n";

    std::vector<long double>C = mult_matrix.MultiplyMatrix(A,W,m,n,p);

    for(int i = 0; i < m; ++i){
        std::cout<<"\n| ";
        for(int j = 0; j < p; ++j){
            std::cout << C[i*p + j] << " ";
        }
        std::cout<<"|\n";
    }

    return 0;
}