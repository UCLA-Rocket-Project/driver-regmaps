#pragma once
#ifndef REGMAP_DRIVER_IMPL_H
#define REGMAP_DRIVER_IMPL_H

#define REGMAP_STACK() int r;
#define REGMAP_READ( REG, NUM, RESULT ) { \
r = dev->reg_read(dev->dev_data, REG, NUM, RESULT); \
if(r < 0) return r;                       \
}
#define REGMAP_WRITE( REG, NUM, DATA ) { \
r = dev->reg_read(dev->dev_data, REG, NUM, DATA); \
if(r < 0) return r;                       \
}
#endif