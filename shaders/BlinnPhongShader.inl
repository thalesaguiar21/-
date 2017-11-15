#include "BlinnPhongShader.h"

BlinnPhongShader::BlinnPhongShader( void ) {
	set_shader_value(0.f);
}

BlinnPhongShader::BlinnPhongShader(float value) {
	set_shader_value(value);
}

RGB BlinnPhongShader::OnHit(Ray r_, World world, HitRecord rec) {
	RGB ambient (1);
	Vector3 light_ray;
	Vector3 view_dir;
	Vector3 half_way;
	Vector3 diffuse;
	Vector3 specular;
	Ray shadow_ray;
	float nl_dot;
	float nh_dot;
	RGB color (0.f);
	vector<Light*> lights = world.lights;

	for(int i = 0; i < lights.size(); i++) {
		if(lights[i]->IsIlluminating(rec.hit)){
			HitRecord tmp;
			
			light_ray = UnitVector(lights[i]->origin() - rec.hit);
			view_dir = UnitVector(r_.origin - rec.hit);
			half_way = UnitVector(view_dir + light_ray);
			
			nl_dot = std::max(0.0f, dot(rec.normal, light_ray));

			diffuse += rec.mat->prop().Y() * nl_dot * rec.mat->diffuse();
			shadow_ray = lights[i]->GetShadowRay(rec.hit);

			Point3 tmpHit = shadow_ray.PointAt(SHADOW_ERROR);
			float shadow_ray_length = (lights[i]->origin() - tmpHit).Length();

			if(!world.HitAnything(shadow_ray, tmp, SHADOW_ERROR, shadow_ray_length)) {
				
				nh_dot = std::max(0.0f, dot(rec.normal, half_way));

				// std::cout << "NHDOT: " << nh_dot << std::endl;
				specular = rec.mat->prop().Z() * 
									 std::pow(nh_dot, shader_value()) * 
									 rec.mat->diffuse();
				color += specular + diffuse;
				
			}
		}
	}
	// std::cout << "COLOR: " << rec.mat->diffuse() << std::endl;
	// std::cout << "COLOR: " << color << std::endl;
	return color;
}
