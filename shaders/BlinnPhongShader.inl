#include "BlinnPhongShader.h"

BlinnPhongShader::BlinnPhongShader( void ) {
	set_shader_value(0.f);
}

BlinnPhongShader::BlinnPhongShader(float value) {
	set_shader_value(value);
}

RGB BlinnPhongShader::GetColor(Ray r_, World world) {
	HitRecord rec;
	RGB ambient (0.8, 0.3, 0.5);
	if(world.HitAnything(r_, rec)) {
		Vector3 light_ray;
		Vector3 view_dir;
		Vector3 half_way;
		Vector3 diffuse;
		Vector3 specular;
		Ray shadow_ray;
		float nl_dot;
		float nh_dot;
		RGB color = rec.mat->prop.Z() * ambient;
		vector<Light*> lights = world.lights;

		for(int i = 0; i < lights.size(); i++) {
			if(lights[i]->IsIlluminating(rec.hit)){
				HitRecord tmp;
				
				light_ray = UnitVector(lights[i]->origin() - rec.hit);
				view_dir = UnitVector(r_.origin - rec.hit);
				half_way = UnitVector(view_dir + light_ray);
				
				nl_dot = std::max(0.000001f, dot(rec.normal, light_ray));

				diffuse = rec.mat->prop.X() * nl_dot * rec.mat->diffCol;
				shadow_ray = lights[i]->GetShadowRay(rec.hit);

				if(!world.HitAnything(shadow_ray, tmp)) {
					nh_dot = std::max(0.000001f, dot(rec.normal, half_way));
					specular = rec.mat->prop.Y() * 
										 std::pow(nh_dot, shader_value()) * 
										 rec.mat->specCol;
					color += specular + diffuse;
				}
			}
		}
		return color;
	} else {
		Vector3 unit_direction = UnitVector(r_.Direction());
    float t = 0.5 * (unit_direction.Y() + 1.0);
    return (1.0 - t)*RGB(1.0, 1.0, 1.0) + t*RGB(0.5, 0.7, 1.0);
	}
}
