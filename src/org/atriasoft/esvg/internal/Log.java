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
	
	public static void critical(final String data) {
		if (Log.PRINT_CRITICAL || Log.FORCE_ALL) {
			Logger.critical(Log.LIB_NAME_DRAW, data);
		}
	}
	
	public static void debug(final String data) {
		if (Log.PRINT_DEBUG || Log.FORCE_ALL) {
			Logger.debug(Log.LIB_NAME_DRAW, data);
		}
	}
	
	public static void error(final String data) {
		if (Log.PRINT_ERROR || Log.FORCE_ALL) {
			Logger.error(Log.LIB_NAME_DRAW, data);
		}
	}
	
	public static void info(final String data) {
		if (Log.PRINT_INFO || Log.FORCE_ALL) {
			Logger.info(Log.LIB_NAME_DRAW, data);
		}
	}
	
	public static void print(final String data) {
		if (Log.PRINT_PRINT || Log.FORCE_ALL) {
			Logger.print(Log.LIB_NAME_DRAW, data);
		}
	}
	
	public static void todo(final String data) {
		if (Log.PRINT_TODO || Log.FORCE_ALL) {
			Logger.todo(Log.LIB_NAME_DRAW, data);
		}
	}
	
	public static void verbose(final String data) {
		if (Log.PRINT_VERBOSE || Log.FORCE_ALL) {
			Logger.verbose(Log.LIB_NAME_DRAW, data);
		}
	}
	
	public static void warning(final String data) {
		if (Log.PRINT_WARNING || Log.FORCE_ALL) {
			Logger.warning(Log.LIB_NAME_DRAW, data);
		}
	}
	
	private Log() {}
	
}
