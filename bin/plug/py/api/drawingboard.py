"""API for plugin writers to adhere to.

Engine shall instantiate the drawingboard module.
"""

import os
import sys
import pprint
pp = pprint.PrettyPrinter(indent=4)

class DrawingBoardInitError(Exception):
	pass


class drawingboard(object):
	"""static class drawingboard instantiated by the Engine"""
	def __init__(self):
		raise DrawingBoardInitError("static class")

	def version(self):
		pass

	def log_message(self, sender, data):
		pass

	def log_error(self, sender, data):
		pass

	def get_all_market_names(self):		
		pass

	def get_all_market_streams(self, market = "default"):
		pass

	def get_schema_for_stream(self, stream):
		pass

	def get_input_command(self, commandname):
		pass

	def get_output_command(self, commandname):
		pass

	def get_all_input_command(self):
		pass

	def get_all_output_command(self):
		pass

	def get_stats_for_command(self, commandname):
		pass

	def set_new_stream(self, stream, schema, provider):
		pass

	def set_provider(self, stream, provider):
		pass

	def register_provider(self, stream, filter, provider):
		pass

	def unregister_provider(self, stream, provider):
		pass

	def onData(self, stream, driver, data):
		pass

	# events - TODO
	# Document the methods, remove redundant, provide example usages
















