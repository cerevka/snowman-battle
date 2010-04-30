
#include "player.h"

double Player::playerSize = 55.0;
double Player::stepSize = 2.5;
int Player::respawnTimeFrames = 250;
int Player::cooldownTimeFrames = 30;


#include "weaponpackage.h"

double WeaponPackage::weaponPackageSizeX = 70.0;
double WeaponPackage::weaponPackageSizeY = 20.0;


#include "handgun.h"

double HandGun::shotSpeed = 10.0;


#include "machinegun.h"

int MachineGun::maxAmmo = 5;
double MachineGun::shotSpeed = 12.0;
double MachineGun::spreadAngle = 0.05;
int MachineGun::batchOfShots = 20;
int MachineGun::cooldownBatchFrames = 5;


#include "shotgun.h"

int ShotGun::maxAmmo = 4;
double ShotGun::shotSpeed = 14.0;
double ShotGun::spreadAngle = 0.1;


