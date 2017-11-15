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
	RGB color = RGB(1.0, 1.0, 1.0) * rec.mat->prop().X();
	vector<Light*> lights = world.lights;
	HitRecord tmp;

	for(int i = 0; i < lights.size(); i++) {
		if(lights[i]->IsIlluminating(rec.hit)){
			shadow_ray = lights[i]->GetShadowRay(rec.hit);	
			Point3 tmpHit = shadow_ray.PointAt(SHADOW_ERROR);
			float shadow_ray_length = (lights[i]->origin() - tmpHit).Length();

			if(!world.HitAnything(shadow_ray, tmp, SHADOW_ERROR, shadow_ray_length)) {
				light_ray = UnitVector(lights[i]->origin() - rec.hit);
				// std::cout <<
				view_dir = UnitVector(r_.origin - rec.hit);
				half_way = UnitVector(view_dir + light_ray);
				float intensity_i = lights[i]->intensity(rec.hit);
				
				nl_dot = std::max(0.0f, dot(rec.normal, light_ray));
				diffuse += rec.mat->prop().Y() * nl_dot * rec.mat->diffuse() * intensity_i;
		
				nh_dot = std::max(0.0f, dot(rec.normal, half_way));
				specular = rec.mat->prop().Z() * 
									 std::pow(nh_dot, shader_value()) * 
									 rec.mat->specular() *
									 intensity_i;
				color += specular + diffuse;
			}
		}
	}
	RGB color_aux = RGB(std::min(color.R(), 1.f),
											std::min(color.G(), 1.f),
											std::min(color.B(), 1.f));
	return color_aux;
}
