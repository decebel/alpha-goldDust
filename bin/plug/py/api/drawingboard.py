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

# TODO - doc strings and group the apis based on usage. caller etc
class DataCommand(object):
	is_command = True

	def set_display_name(self, name):
		pass

	def get_display_name(self):
		pass

	def get_status_string(self):
		pass

	def set_status_string(self):
		pass

	def set_icon(self, resource):
		pass

	def get_icon(self):
		pass

	def init(self):
		pass

	def is_initialized(self):
		pass

	def stop(self):
		pass

	def is_stopped(self):
		pass

	def suspend(self):
		pass

	def is_suspended(self):
		pass

	def shutdown(self):
		pass

	def is_shutdown(self):
		pass

	def can_batch(self):
		pass

	def set_batchsize(self, size):
		pass

	def get_batchsize(self):
		pass

	def set_flush_interval(self, interval):
		pass

	def get_flush_interval(self):
		pass

	def subscribe_my_stats(self, callback):
		"""If someone is interested in the DataCommand stats, they can provide a callback."""
		pass

	def on_new_stream(self, stream, schema):
		pass

	def set_port_hints(self):
		pass

	# should we make the get/set as properties?	
	def set_input_port_count(self, count):
		pass

	def set_output_port_count(self, count):
		pass

	def get_input_port_count(self):
		pass

	def get_output_port_count(self):
		pass

	def set_output_port_schema(self, port, schema):
		pass

	def get_output_port_schema(self, port):
		pass

	def set_input_port_schema(self, port, schema):
		pass

	def get_input_port_schema(self, port):
		pass

	def submit_command(self, port, commandArgs):
		pass

	def send_output(self, port, data):
		pass

	def send_output_async(self, port, data):
		pass

	def cancel_last_command(self):
		pass

	def is_command_canceled(self):
		pass

	def send_error_port(self, data):
		pass

	def send_admin_port(self, status):
		pass

	def has_admin_port(self):
		pass

	def check_connections(self):
		"""typecheck schema for ports."""
		pass

	def get_params(self):
		pass

	def set_params(self, **kwParams):
		pass

	#event subscription todo

	def resume(self):
		pass

	def is_resumed(self):
		pass



def list_directory(directory, fileExt = ".py"):
	fileList = [f for f in os.listdir(directory)]
	fileList = [os.path.splitext(f)[0] for f in fileList if os.path.splitext(f)[1] in fileExt]
	return fileList

















