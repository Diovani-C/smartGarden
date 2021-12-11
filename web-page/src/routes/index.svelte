<script lang="ts">
	import Chart from '$lib/components/Chart.svelte';
	import Irrigation from '$lib/components/Irrigation.svelte';
	import TimePicker from '$lib/components/TimePicker.svelte';
	import { parseCSV, fillTheLastXValue } from '$lib/utilities';
	import { onMount } from 'svelte';

	const sensorsDecoration = [
		{ label: 'Umidade do Ar %', color: '#009dff' },
		{ label: 'Temperatura ºC', color: '#fc4b6f' },
		{ label: 'Umidade do Solo %', color: '#e5682b' }
	];

	let datasets: Dataset[] = [];
	let minDate = '';
	let maxDate = '';

	onMount(async () => {
		const csv = await fetch('/sensorData.csv');
		if (csv.ok) {
			const parsedSensorData = fillTheLastXValue(parseCSV(await csv.text()));

			const updatedDatasets: Dataset[] = [];

			for (let i = 0; i < parsedSensorData.length; i++) {
				const sensorData = sensorsDecoration[parsedSensorData[i].ID - 1];

				updatedDatasets.push({
					label: sensorData.label,
					data: parsedSensorData[i].data,
					borderColor: sensorData.color
				});
			}

			datasets = updatedDatasets;
			minDate = getDate(datasets[0].data[0].x);
			maxDate = getDate(datasets[0].data[datasets[0].data.length - 1].x);
		} else {
			alert('Could not fetch csv file');
		}
	});

	function getDate(utc: number): string {
		const utcDate = new Date(utc);
		return `${utcDate.getFullYear()}-${utcDate.getMonth() + 1}-${utcDate.getDate()}`;
	}
</script>

<div>
	{#if datasets.length > 0}
		<Chart title="Horta Inteligente" {datasets} min={-10} max={100} />
	{/if}
</div>
<TimePicker min={minDate} max={maxDate} />
<Irrigation />

<style>
	div {
		aspect-ratio: 2/1;
		max-width: 100%;
		max-height: 100%;
		margin-bottom: 24px;
	}
</style>
