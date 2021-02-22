package org.atriasoft.esvg.internal;

import io.scenarium.logger.LogLevel;
import io.scenarium.logger.Logger;

class Log {
	private static final String LIB_NAME = "esvg";
	private static final String LIB_NAME_DRAW = Logger.getDrawableName(LIB_NAME);
	private static final boolean PRINT_CRITICAL = Logger.getNeedPrint(LIB_NAME, LogLevel.CRITICAL);
	private static final boolean PRINT_ERROR = Logger.getNeedPrint(LIB_NAME, LogLevel.ERROR);
	private static final boolean PRINT_WARNING = Logger.getNeedPrint(LIB_NAME, LogLevel.WARNING);
	private static final boolean PRINT_INFO = Logger.getNeedPrint(LIB_NAME, LogLevel.INFO);
	private static final boolean PRINT_DEBUG = Logger.getNeedPrint(LIB_NAME, LogLevel.DEBUG);
	private static final boolean PRINT_VERBOSE = Logger.getNeedPrint(LIB_NAME, LogLevel.VERBOSE);
	private static final boolean PRINT_TODO = Logger.getNeedPrint(LIB_NAME, LogLevel.TODO);
	private static final boolean PRINT_PRINT = Logger.getNeedPrint(LIB_NAME, LogLevel.PRINT);
	
	public static void critical(final String data) {
		if (PRINT_CRITICAL) {
			Logger.critical(LIB_NAME_DRAW, data);
		}
	}
	
	public static void debug(final String data) {
		if (PRINT_DEBUG) {
			Logger.debug(LIB_NAME_DRAW, data);
		}
	}
	
	public static void error(final String data) {
		if (PRINT_ERROR) {
			Logger.error(LIB_NAME_DRAW, data);
		}
	}
	
	public static void info(final String data) {
		if (PRINT_INFO) {
			Logger.info(LIB_NAME_DRAW, data);
		}
	}
	
	public static void print(final String data) {
		if (PRINT_PRINT) {
			Logger.print(LIB_NAME_DRAW, data);
		}
	}
	
	public static void todo(final String data) {
		if (PRINT_TODO) {
			Logger.todo(LIB_NAME_DRAW, data);
		}
	}
	
	public static void verbose(final String data) {
		if (PRINT_VERBOSE) {
			Logger.verbose(LIB_NAME_DRAW, data);
		}
	}
	
	public static void warning(final String data) {
		if (PRINT_WARNING) {
			Logger.warning(LIB_NAME_DRAW, data);
		}
	}
	
	private Log() {}
	
}
