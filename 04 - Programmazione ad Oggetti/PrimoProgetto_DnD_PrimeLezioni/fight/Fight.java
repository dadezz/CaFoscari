package PrimoProgetto_DnD_PrimeLezioni.fight;

import java.util.Random;

import PrimoProgetto_DnD_PrimeLezioni.characters.Fighter;

public class Fight {
    private Fighter f1, f2;

    public Fight(Fighter f1, Fighter f2) {
        this.f1 = f1;
        this.f2 = f2;
    }

    private boolean singleFight() {
        Random random = new Random();
        if(f1.isAlive() && f2.isAlive()) {
            if(random.nextDouble()>=0.5) {
                f2.getDamaged(f1.getWeaponDamage());
                f1.setWeaponDamage(f1.getWeaponDamage()-1);
            }
            else {
                f1.getDamaged(f2.getWeaponDamage());
                f2.setWeaponDamage(f2.getWeaponDamage()-1);
            }
        }
        return f1.isAlive() && f2.isAlive();
    }

    public int fight() {
        while(this.singleFight());
        if(f1.isAlive()) {
            f1.defeated(f2);
            return 1;
        }
        else {f2.defeated(f1);
            return 2;
        }
    }

}
