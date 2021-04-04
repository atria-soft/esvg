package org.atriasoft.esvg.render;

public enum PointType {
	interpolation, //!< Point type is single, this mean that it start and stop of a path
	join, //!< Point type is starting of a path
	single, //!< Point type is stoping of a path
	start, //!< Point type in an user point provided inside a path
	stop; //!< This point is dynamicly calculated to create an interpolation

}
