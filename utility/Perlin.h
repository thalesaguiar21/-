#ifndef _PERLIN_H_
#define _PERLIN_H_

namespace utils {

	inline float TrilinearInterp(Vector3 c[2][2][2], float u, float v, float w) {
		float acumm = 0.f;
		float uu = u*u*(3-2*u);
		float vv = v*v*(3-2*v);
		float ww = w*w*(3-2*w);
		for(int i= 0; i< 2; i++) {
			for(int j= 0; j< 2; j++) {
				for(int k= 0;k < 2; k++) {
					Vector3 weight (u-i, v-j, w-k);
					acumm += (i*uu + (1-i)*(1-uu))*
									 (j*vv + (1-j)*(1-vv))*
									 (k*ww + (1-k)*(1-ww))*
									 dot(c[i][j][k], weight);
				}
			}
		}
		return acumm;
	}

	class Perlin {
	public:
		float Noise(const Vector3 &p) const {
			Vector3 pAux = p;
			float u = pAux.X() - floor(pAux.X());
			float v = pAux.Y() - floor(pAux.Y());
			float w = pAux.Z() - floor(pAux.Z());
			int i = floor(pAux.X());
			int j = floor(pAux.Y());
			int k = floor(pAux.Z());

			Vector3 c[2][2][2];
			for(int di= 0; di< 2; di++) {
				for(int dj= 0; dj< 2; dj++) {
					for(int dk= 0;dk < 2; dk++) {
						c[di][dj][dk] = ranVec[perm_x[(i+di) & 255] ^ perm_y[(j+dj) & 255] ^ perm_z[(k+dk) & 255]];
					}
				}
			}
			return TrilinearInterp(c, u, v, w);
		}

		float turb(const Vector3& p, int depth=7) {
			float acum = 0;
			Vector3 tmp_p = p;
			float weight = 1.0;
			for (int i = 0; i < depth; i++)
			{
				acum += weight*Noise(tmp_p);
				weight *= 0.5;
				tmp_p *= 2;
			}

			return fabs(acum);
		}

		static Vector3 *ranVec;
		static int *perm_x;
		static int *perm_y;
		static int *perm_z;		
	};

	static Vector3* PerlinGenerate() {
		Vector3 *p = new Vector3[256];
		for(int i=0; i<256; ++i) {
			p[i] = UnitVector(Vector3(-1 +2*drand48(), -1 +2*drand48(), -1 +2*drand48()));
		}
		return p;
	}

	void permute(int *p, int n) {
		for(int i=n-1; i>0; i--) {
			int target = int(drand48()*(i+1));
			int tmp = p[i];
			p[i] = p[target];
			p[target] = tmp;
		}
	}

	static int* PerlinGeneratePerm() {
		int *p = new int[256];
		for(int i=0; i<256; i++) {
			p[i] = i;
		}
		permute(p, 256);
		return p;
	}

	Vector3 *Perlin::ranVec = PerlinGenerate();
	int *Perlin::perm_x = PerlinGeneratePerm();
	int *Perlin::perm_y = PerlinGeneratePerm();
	int *Perlin::perm_z = PerlinGeneratePerm();

}

#endif