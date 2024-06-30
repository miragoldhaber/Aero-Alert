#ifndef COORD_HPP
#define COORD_HPP
struct coord {
  double latitude;
  char lat;
  double longitude;
  char lon;
  double altitude;

  coord() = default;

  coord(double latitude, char lat, double longitude, char lon, double altitude)
      : latitude(latitude),
        lat(lat),
        longitude(longitude),
        lon(lon),
        altitude(altitude) {}
};

#endif //COORD_HPP