#ifndef UJER_EATS_COLLISION_H
#define UJER_EATS_COLLISION_H

#define CHECK_COLLISION_POINT_REC(point, rec) ((point.x >= rec.x) && (point.x <= (rec.x + rec.width)) && (point.y >= rec.y) && (point.y <= (rec.y + rec.height)))

#endif //UJER_EATS_COLLISION_H