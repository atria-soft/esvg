package org.atriasoft.esvg.internal;

import io.scenarium.logger.LogLevel;
import io.scenarium.logger.Logger;

public class Log {
	private static final boolean FORCE_ALL = false;
	private static final String LIB_NAME = "esvg";
	private static final String LIB_NAME_DRAW = Logger.getDrawableName(Log.LIB_NAME);
	private static final boolean PRINT_CRITICAL = Logger.getNeedPrint(Log.LIB_NAME, LogLevel.CRITICAL);
	private static final boolean PRINT_DEBUG = Logger.getNeedPrint(Log.LIB_NAME, LogLevel.DEBUG);
	private static final boolean PRINT_ERROR = Logger.getNeedPrint(Log.LIB_NAME, LogLevel.ERROR);
	private static final boolean PRINT_INFO = Logger.getNeedPrint(Log.LIB_NAME, LogLevel.INFO);
	private static final boolean PRINT_PRINT = Logger.getNeedPrint(Log.LIB_NAME, LogLevel.PRINT);
	private static final boolean PRINT_TODO = Logger.getNeedPrint(Log.LIB_NAME, LogLevel.TODO);
	private static final boolean PRINT_VERBOSE = Logger.getNeedPrint(Log.LIB_NAME, LogLevel.VERBOSE);
	private static final boolean PRINT_WARNING = Logger.getNeedPrint(Log.LIB_NAME, LogLevel.WARNING);
	
	public static void critical(final Exception e, final String data) {
		e.printStackTrace();
		if (PRINT_CRITICAL || FORCE_ALL) {
			Logger.critical(LIB_NAME_DRAW, data + " : " + e.getMessage());
		}
	}
	
	public static void critical(final String data, final Object... objects) {
		if (PRINT_CRITICAL || FORCE_ALL) {
			Logger.critical(LIB_NAME_DRAW, data, objects);
		}
	}
	
	public static void debug(final String data, final Object... objects) {
		if (PRINT_DEBUG || FORCE_ALL) {
			Logger.debug(LIB_NAME_DRAW, data, objects);
		}
	}
	
	public static void error(final String data, final Object... objects) {
		if (PRINT_ERROR || FORCE_ALL) {
			Logger.error(LIB_NAME_DRAW, data, objects);
		}
	}
	
	public static void info(final String data, final Object... objects) {
		if (PRINT_INFO || FORCE_ALL) {
			Logger.info(LIB_NAME_DRAW, data, objects);
		}
	}
	
	public static void print(final String data, final Object... objects) {
		if (PRINT_PRINT || FORCE_ALL) {
			Logger.print(LIB_NAME_DRAW, data, objects);
		}
	}
	
	public static void todo(final String data, final Object... objects) {
		if (PRINT_TODO || FORCE_ALL) {
			Logger.todo(LIB_NAME_DRAW, data, objects);
		}
	}
	
	public static void verbose(final String data, final Object... objects) {
		if (PRINT_VERBOSE || FORCE_ALL) {
			Logger.verbose(LIB_NAME_DRAW, data, objects);
		}
	}
	
	public static void warning(final String data, final Object... objects) {
		if (PRINT_WARNING || FORCE_ALL) {
			Logger.warning(LIB_NAME_DRAW, data, objects);
		}
	}
	
	private Log() {}
	
}
