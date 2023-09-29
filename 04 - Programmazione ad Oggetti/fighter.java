public class fighter {
    int experience_point = 0;
    int life_points = 100;
    Weapon weapon;
    Armor armor;
    int get_level() {
        return experience_point/1000 + 1;
    }
    void get_damage(Weapon w){
        int OverallDamage = w.damage - armor.defence;
        if (OverallDamage>0) {
            if (OverallDamage<=life_points) {
                life_points = life_points - OverallDamage;
            }
            else life_points = 0;
        }
    }
}
