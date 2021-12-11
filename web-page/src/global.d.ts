/// <reference types="@sveltejs/kit" />
type SensorData = { ID: number; data: { x: number; y: number }[] };

type Dataset = {
	label: string;
	borderColor: string;
	data: SensorData['data'];
};

type State = {
	from: string;
	to: string;
};
